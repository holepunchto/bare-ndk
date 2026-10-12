#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <string>
#include <sys/timerfd.h>
#include <unistd.h>
#include <uv.h>
#include <vector>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/looper.h>
#include <android/native_activity.h>

#define BARE_EXTRACTION_CONCURRENCY 16

typedef struct {
  AAssetManager *manager;
  std::string directory;
  std::vector<std::string> keys;
  size_t next;
  size_t active;
  bool listed;
} bare_extraction_t;

typedef struct {
  uv_fs_t req;
  bare_extraction_t *extraction;
  AAsset *asset;
  std::string target;
  size_t parent;
  uv_file file;
  uv_buf_t pending;
  char buffer[65536];
} bare_extraction_copy_t;

static uv_barrier_t bare__platform_ready;
static uv_async_t bare__platform_shutdown;
static uv_thread_t bare__platform_thread;
static js_platform_t *bare__platform;

static uv_loop_t *bare__loop;
static uv_async_t bare__shutdown;
static bare_t *bare;

static int bare__timer;

static ANativeActivity bare__native_activity;
static AAsset *bare__bundle = nullptr;
static bool bare__started = false;

ANativeActivity *bare_native_activity = &bare__native_activity;

static void
bare__on_shutdown(uv_async_t *handle) {
  uv_close(reinterpret_cast<uv_handle_t *>(handle), nullptr);
}

static void
bare__on_platform_thread(void *data) {
  int err;

  uv_loop_t loop;
  err = uv_loop_init(&loop);
  assert(err == 0);

  err = uv_async_init(&loop, &bare__platform_shutdown, bare__on_shutdown);
  assert(err == 0);

  err = js_create_platform(&loop, nullptr, &bare__platform);
  assert(err == 0);

  uv_barrier_wait(&bare__platform_ready);

  err = uv_run(&loop, UV_RUN_DEFAULT);
  assert(err == 0);

  err = js_destroy_platform(bare__platform);
  assert(err == 0);

  err = uv_run(&loop, UV_RUN_DEFAULT);
  assert(err == 0);

  err = uv_loop_close(&loop);
  assert(err == 0);
}

static void
bare__arm(void) {
  int timeout = uv_backend_timeout(bare__loop);

  struct itimerspec spec = {0};

  if (timeout > 0) {
    spec.it_value.tv_sec = timeout / 1000;
    spec.it_value.tv_nsec = (timeout % 1000) * 1000000;
  } else if (timeout == 0) {
    // An all-zero `it_value` stops the timer instead of firing it.
    spec.it_value.tv_nsec = 1;
  }

  timerfd_settime(bare__timer, 0, &spec, nullptr);
}

static void
bare__run(void) {
  int err;

  err = bare_run(bare, UV_RUN_NOWAIT);
  assert(err >= 0);

  if (uv_backend_timeout(bare__loop) == 0) return bare__run();

  bare__arm();
}

// Only the pump arms the timer, so work scheduled from a Java callback would
// wait until something else woke the loop. Android has no hook for the moment
// before the looper sleeps, so an addon that calls into JavaScript says so.
extern "C" void
bare_native_wake(void) {
  bare__arm();
}

static int
bare__on_poll(int fd, int events, void *data) {
  bare__run();

  return 1;
}

static int
bare__on_timeout(int fd, int events, void *data) {
  bare__run();

  return 1;
}

static void
bare__extract_next(bare_extraction_t *extraction);

static void
bare__extract_parent(bare_extraction_copy_t *copy);

static void
bare__extract_chunk(bare_extraction_copy_t *copy);

static void
bare__on_extract_close(uv_fs_t *req) {
  auto copy = reinterpret_cast<bare_extraction_copy_t *>(req);

  assert(req->result == 0);

  uv_fs_req_cleanup(req);

  AAsset_close(copy->asset);

  auto extraction = copy->extraction;

  extraction->active--;

  delete copy;

  bare__extract_next(extraction);
}

static void
bare__on_extract_write(uv_fs_t *req) {
  auto copy = reinterpret_cast<bare_extraction_copy_t *>(req);

  assert(req->result > 0);

  size_t written = req->result;

  uv_fs_req_cleanup(req);

  copy->pending.base += written;
  copy->pending.len -= written;

  if (copy->pending.len > 0) {
    int err = uv_fs_write(bare__loop, req, copy->file, &copy->pending, 1, -1, bare__on_extract_write);
    assert(err == 0);
  } else {
    bare__extract_chunk(copy);
  }
}

static void
bare__extract_chunk(bare_extraction_copy_t *copy) {
  int err;

  int read = AAsset_read(copy->asset, copy->buffer, sizeof(copy->buffer));
  assert(read >= 0);

  if (read == 0) {
    err = uv_fs_close(bare__loop, &copy->req, copy->file, bare__on_extract_close);
    assert(err == 0);

    return;
  }

  copy->pending = uv_buf_init(copy->buffer, read);

  err = uv_fs_write(bare__loop, &copy->req, copy->file, &copy->pending, 1, -1, bare__on_extract_write);
  assert(err == 0);
}

static void
bare__on_extract_open(uv_fs_t *req) {
  auto copy = reinterpret_cast<bare_extraction_copy_t *>(req);

  assert(req->result >= 0);

  copy->file = req->result;

  uv_fs_req_cleanup(req);

  bare__extract_chunk(copy);
}

static void
bare__on_extract_mkdir(uv_fs_t *req) {
  auto copy = reinterpret_cast<bare_extraction_copy_t *>(req);

  assert(req->result == 0 || req->result == UV_EEXIST);

  uv_fs_req_cleanup(req);

  copy->parent = copy->target.find('/', copy->parent + 1);

  bare__extract_parent(copy);
}

static void
bare__extract_parent(bare_extraction_copy_t *copy) {
  int err;

  if (copy->parent == std::string::npos) {
    err = uv_fs_open(bare__loop, &copy->req, copy->target.c_str(), UV_FS_O_WRONLY | UV_FS_O_CREAT | UV_FS_O_TRUNC, 0600, bare__on_extract_open);
    assert(err == 0);
  } else {
    err = uv_fs_mkdir(bare__loop, &copy->req, copy->target.substr(0, copy->parent).c_str(), 0700, bare__on_extract_mkdir);
    assert(err == 0);
  }
}

static void
bare__extract(bare_extraction_t *extraction, const std::string &name, const std::string &target) {
  auto copy = new bare_extraction_copy_t();

  copy->extraction = extraction;
  copy->asset = AAssetManager_open(extraction->manager, name.c_str(), AASSET_MODE_STREAMING);
  assert(copy->asset != nullptr);

  copy->target = target;
  copy->parent = target.find('/', 1);

  extraction->active++;

  bare__extract_parent(copy);
}

static void
bare__extract_next(bare_extraction_t *extraction) {
  while (extraction->next < extraction->keys.size() && extraction->active < BARE_EXTRACTION_CONCURRENCY) {
    auto &key = extraction->keys[extraction->next++];

    bare__extract(extraction, "app" + key, extraction->directory + "/app" + key);
  }

  if (extraction->active > 0 || extraction->next < extraction->keys.size() || extraction->listed) return;

  extraction->listed = true;

  bare__extract(extraction, "app.assets", extraction->directory + "/app.assets");
}

static void
bare__extract_assets(AAssetManager *manager, const std::string &directory) {
  int err;

  uv_fs_t req;
  err = uv_fs_access(bare__loop, &req, (directory + "/app.assets").c_str(), F_OK, nullptr);
  uv_fs_req_cleanup(&req);

  if (err == 0) return;

  AAsset *list = AAssetManager_open(manager, "app.assets", AASSET_MODE_BUFFER);

  if (list == nullptr) return;

  std::string keys(static_cast<const char *>(AAsset_getBuffer(list)), AAsset_getLength(list));

  AAsset_close(list);

  bare_extraction_t extraction = {manager, directory, {}, 0, 0, false};

  for (size_t start = 0, end; (end = keys.find('\n', start)) != std::string::npos; start = end + 1) {
    extraction.keys.push_back(keys.substr(start, end - start));
  }

  bare__extract_next(&extraction);

  err = uv_run(bare__loop, UV_RUN_DEFAULT);
  assert(err == 0);
}

extern "C" void
Java_to_holepunch_bare_Activity_setup(JNIEnv *env, jobject self, jobject state, jobject assets, jstring cache) {
  int err;

  // What follows runs once per process, so a new activity only has to be taken
  // on. The old tree went away with the old activity.
  if (bare__started) {
    env->DeleteGlobalRef(bare__native_activity.clazz);

    bare__native_activity.env = env;
    bare__native_activity.clazz = env->NewGlobalRef(self);
    bare__native_activity.assetManager = AAssetManager_fromJava(env, assets);

    return;
  }

  bare__started = true;

  bare__native_activity.env = env;

  bare__native_activity.clazz = env->NewGlobalRef(self);

  bare__native_activity.assetManager = AAssetManager_fromJava(env, assets);

  uv_setup_args(0, nullptr);

  err = uv_barrier_init(&bare__platform_ready, 2);
  assert(err == 0);

  err = uv_thread_create(&bare__platform_thread, bare__on_platform_thread, nullptr);
  assert(err == 0);

  uv_barrier_wait(&bare__platform_ready);

  uv_barrier_destroy(&bare__platform_ready);

  bare__loop = uv_default_loop();

  std::string directory = java_string_t(env, cache);

  bare__extract_assets(bare__native_activity.assetManager, directory);

  err = uv_async_init(bare__loop, &bare__shutdown, bare__on_shutdown);
  assert(err == 0);

  err = bare_setup(bare__loop, bare__platform, nullptr, 0, nullptr, nullptr, &bare);
  assert(err == 0);

  JavaVM *vm;
  err = env->GetJavaVM(&vm);
  assert(err == 0);

  err = bare_context_set(bare, "bare.android.jvm.v1", vm, nullptr);
  assert(err == 0);

  bare__bundle = AAssetManager_open(bare__native_activity.assetManager, "app.bundle", AASSET_MODE_BUFFER);

  uv_buf_t entry = uv_buf_init((char *) AAsset_getBuffer(bare__bundle), AAsset_getLength(bare__bundle));

  err = bare_load(bare, (directory + "/app.bundle").c_str(), &entry, nullptr);
  (void) err;

  ALooper *looper = ALooper_forThread();

  err = ALooper_addFd(looper, bare__loop->backend_fd, ALOOPER_POLL_CALLBACK, ALOOPER_EVENT_INPUT, bare__on_poll, nullptr);
  assert(err == 1);

  bare__timer = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

  err = ALooper_addFd(looper, bare__timer, ALOOPER_POLL_CALLBACK, ALOOPER_EVENT_INPUT, bare__on_timeout, nullptr);
  assert(err == 1);

  bare__run();
}

extern "C" void
Java_to_holepunch_bare_Activity_teardown(JNIEnv *env, jobject self) {
  int err;

  ALooper *looper = ALooper_forThread();

  err = ALooper_removeFd(looper, bare__loop->backend_fd);
  assert(err == 1);

  err = ALooper_removeFd(looper, bare__timer);
  assert(err == 1);

  close(bare__timer);

  err = uv_async_send(&bare__shutdown);
  assert(err == 0);

  err = bare_terminate(bare);
  assert(err == 0);

  err = bare_run(bare, UV_RUN_NOWAIT);
  assert(err >= 0);

  err = bare_teardown(bare, UV_RUN_DEFAULT, nullptr);
  assert(err >= 0);

  err = uv_loop_close(bare__loop);
  assert(err == 0);

  err = uv_async_send(&bare__platform_shutdown);
  assert(err == 0);

  uv_thread_join(&bare__platform_thread);

  AAsset_close(bare__bundle);

  bare__started = false;
}

extern "C" void
Java_to_holepunch_bare_Activity_suspend(JNIEnv *env, jobject self) {
  int err;

  err = bare_suspend(bare, 0);
  assert(err == 0);
}

extern "C" void
Java_to_holepunch_bare_Activity_resume(JNIEnv *env, jobject self) {
  int err;

  err = bare_resume(bare);
  assert(err == 0);
}
