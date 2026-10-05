#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

// Each looper thread has a choreographer of its own, and this is the one of the
// thread the engine runs on.
static js_value_t *
bare_ndk_choreographer_get_instance(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  JNIEnv *jni = bare_jni_env();

  auto type = java_class_t<"android/view/Choreographer">(jni, bare_ndk__class<"android/view/Choreographer">(jni));

  return bare_ndk__tag(env, state, type.get_static_method<java_object_t<"android/view/Choreographer">()>("getInstance")());
}

static js_value_t *
bare_ndk_choreographer__frame_callback(js_env_t *env, js_callback_info_t *info, const char *method) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/Choreographer"> choreographer;
  err = bare_ndk__read_object(env, state, argv[0], "choreographer", &choreographer);
  if (err < 0) return nullptr;

  java_object_t<"android/view/Choreographer$FrameCallback"> callback;
  err = bare_ndk__read_object(env, state, argv[1], "callback", &callback);
  if (err < 0) return nullptr;

  choreographer.get_class().get_method<void(java_object_t<"android/view/Choreographer$FrameCallback">)>(method)(choreographer, callback);

  return nullptr;
}

static js_value_t *
bare_ndk_choreographer_post_frame_callback(js_env_t *env, js_callback_info_t *info) {
  return bare_ndk_choreographer__frame_callback(env, info, "postFrameCallback");
}

static js_value_t *
bare_ndk_choreographer_remove_frame_callback(js_env_t *env, js_callback_info_t *info) {
  return bare_ndk_choreographer__frame_callback(env, info, "removeFrameCallback");
}
