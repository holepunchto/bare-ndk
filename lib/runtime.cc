#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <log.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <uv.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/looper.h>
#include <android/native_activity.h>

static uv_barrier_t bare__platform_ready;
static uv_async_t bare__platform_shutdown;
static uv_thread_t bare__platform_thread;
static js_platform_t *bare__platform;

static uv_loop_t *bare__loop;
static uv_async_t bare__shutdown;
static bare_t *bare;

static int bare__timer;

static ANativeActivity bare__native_activity;

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
bare__run(void) {
  int err;

  err = bare_run(bare, UV_RUN_NOWAIT);
  assert(err >= 0);

  int timeout = uv_backend_timeout(bare__loop);

  if (timeout == 0) return bare__run();

  struct itimerspec spec = {0};

  if (timeout > 0) {
    spec.it_value.tv_sec = timeout / 1000;
    spec.it_value.tv_nsec = (timeout % 1000) * 1000000;
  }

  timerfd_settime(bare__timer, 0, &spec, nullptr);
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
bare__on_start(ANativeActivity *activity) {
  int err;
}

static void
bare__on_destroy(ANativeActivity *activity) {
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
}

static void
bare__on_pause(ANativeActivity *activity) {
  int err;

  err = bare_suspend(bare, 0);
  assert(err == 0);
}

static void
bare__on_resume(ANativeActivity *activity) {
  int err;

  err = bare_resume(bare);
  assert(err == 0);
}

extern "C" void
Java_to_holepunch_bare_Activity_onCreate(JNIEnv *env, jobject self, jobject assetManager) {
  int err;

  bare__native_activity.env = env;

  bare__native_activity.clazz = env->NewGlobalRef(self);

  bare__native_activity.assetManager = AAssetManager_fromJava(env, assetManager);

  err = log_open("bare", 0);
  assert(err == 0);

  uv_setup_args(0, nullptr);

  err = uv_barrier_init(&bare__platform_ready, 2);
  assert(err == 0);

  err = uv_thread_create(&bare__platform_thread, bare__on_platform_thread, nullptr);
  assert(err == 0);

  uv_barrier_wait(&bare__platform_ready);

  uv_barrier_destroy(&bare__platform_ready);

  bare__loop = uv_default_loop();

  err = uv_async_init(bare__loop, &bare__shutdown, bare__on_shutdown);
  assert(err == 0);

  err = bare_setup(bare__loop, bare__platform, nullptr, 0, nullptr, nullptr, &bare);
  assert(err == 0);

  AAsset *asset = AAssetManager_open(bare__native_activity.assetManager, "app.bundle", AASSET_MODE_BUFFER);

  uv_buf_t entry = uv_buf_init((char *) AAsset_getBuffer(asset), AAsset_getLength(asset));

  err = bare_load(bare, "bare:/app.bundle", &entry, nullptr);
  (void) err;

  AAsset_close(asset);

  ALooper *looper = ALooper_forThread();

  err = ALooper_addFd(looper, bare__loop->backend_fd, ALOOPER_POLL_CALLBACK, ALOOPER_EVENT_INPUT, bare__on_poll, nullptr);
  assert(err == 1);

  bare__timer = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

  err = ALooper_addFd(looper, bare__timer, ALOOPER_POLL_CALLBACK, ALOOPER_EVENT_INPUT, bare__on_timeout, nullptr);
  assert(err == 1);

  bare__run();
}
