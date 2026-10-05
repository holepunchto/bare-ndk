#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

enum {
  bare_ndk_frame_callback_event_frame = 1 << 0,
};

static void
bare_ndk_frame_callback__on_frame(java_env_t env, java_object_t<"to/holepunch/bare/ndk/FrameCallback"> receiver, int64_t frame_time_nanos) {
  bare_ndk__emit(receiver, "frame", 1, (const double[]) {double(frame_time_nanos)});
}

static void
bare_ndk_frame_callback_register(JNIEnv *jni) {
  java_class_t<"to/holepunch/bare/ndk/FrameCallback">(jni, bare_ndk__class<"to/holepunch/bare/ndk/FrameCallback">(jni))
    .register_natives(
      java_native_method_t<bare_ndk_frame_callback__on_frame>("onFrame")
    );
}

static js_value_t *
bare_ndk_frame_callback_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  JNIEnv *jni = bare_jni_env();

  auto init = java_class_t<"to/holepunch/bare/ndk/FrameCallback">(jni, bare_ndk__class<"to/holepunch/bare/ndk/FrameCallback">(jni));

  return bare_ndk__tag(env, state, init());
}

static js_value_t *
bare_ndk_frame_callback_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"to/holepunch/bare/ndk/FrameCallback"> callback;
  err = bare_ndk__read_object(env, state, argv[0], "callback", &callback);
  if (err < 0) return nullptr;

  int32_t mask;
  err = js_get_value(env, js_number_t(argv[1]), mask);
  assert(err == 0);

  callback.get_class().get_method<void(int32_t)>("setEvents")(callback, mask);

  return nullptr;
}
