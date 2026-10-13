#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

static js_value_t *
bare_ndk_system_clock_uptime_millis(js_env_t *env, js_callback_info_t *info) {
  int err;

  JNIEnv *jni = bare_jni_env();

  auto type = java_class_t<"android/os/SystemClock">(jni, bare_ndk__class<"android/os/SystemClock">(jni));

  js_value_t *result;
  err = js_create_int64(env, type.get_static_method<int64_t()>("uptimeMillis")(), &result);
  assert(err == 0);

  return result;
}
