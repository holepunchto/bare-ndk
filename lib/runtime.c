#include <assert.h>
#include <bare.h>
#include <js.h>
#include <log.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <uv.h>

#include <android/asset_manager.h>
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

static void
bare__on_shutdown(uv_async_t *handle) {
  uv_close((uv_handle_t *) handle, NULL);
}

static void
bare__on_platform_thread(void *data) {
  int err;

  uv_loop_t loop;
  err = uv_loop_init(&loop);
  assert(err == 0);

  err = uv_async_init(&loop, &bare__platform_shutdown, bare__on_shutdown);
  assert(err == 0);

  err = js_create_platform(&loop, NULL, &bare__platform);
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

  timerfd_settime(bare__timer, 0, &spec, NULL);
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

void
ANativeActivity_onCreate(ANativeActivity *activity, void *state, size_t len) {
  int err;

  err = log_open("bare", 0);
  assert(err == 0);

  uv_setup_args(0, NULL);

  err = uv_barrier_init(&bare__platform_ready, 2);
  assert(err == 0);

  err = uv_thread_create(&bare__platform_thread, bare__on_platform_thread, NULL);
  assert(err == 0);

  uv_barrier_wait(&bare__platform_ready);

  uv_barrier_destroy(&bare__platform_ready);

  bare__loop = uv_default_loop();

  err = uv_async_init(bare__loop, &bare__shutdown, bare__on_shutdown);
  assert(err == 0);

  err = bare_setup(bare__loop, bare__platform, NULL, 0, NULL, NULL, &bare);
  assert(err == 0);

  AAsset *asset = AAssetManager_open(activity->assetManager, "app.bundle", AASSET_MODE_BUFFER);

  uv_buf_t entry = uv_buf_init((char *) AAsset_getBuffer(asset), AAsset_getLength(asset));

  err = bare_load(bare, "bare:/app.bundle", &entry, NULL);
  (void) err;

  AAsset_close(asset);

  ALooper *looper = ALooper_forThread();

  err = ALooper_addFd(looper, bare__loop->backend_fd, ALOOPER_POLL_CALLBACK, ALOOPER_EVENT_INPUT, bare__on_poll, NULL);
  assert(err == 1);

  bare__timer = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);

  err = ALooper_addFd(looper, bare__timer, ALOOPER_POLL_CALLBACK, ALOOPER_EVENT_INPUT, bare__on_timeout, NULL);
  assert(err == 1);

  activity->callbacks->onDestroy = bare__on_destroy;
  activity->callbacks->onPause = bare__on_pause;
  activity->callbacks->onResume = bare__on_resume;

  bare__run();
}
