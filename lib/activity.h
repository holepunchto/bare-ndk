#include <assert.h>
#include <bare.h>
#include <js.h>

#include <android/native_activity.h>

extern ANativeActivity *bare_native_activity;

static js_value_t *
bare_ndk_activity_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  js_value_t *handle;
  err = js_create_external(env, bare_native_activity, nullptr, nullptr, &handle);
  assert(err == 0);

  return handle;
}
