#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

static int32_t
bare_ndk__motion_event_constant(const char *name) {
  JNIEnv *jni = bare_jni_env();

  auto type = java_class_t<"android/view/MotionEvent">(jni, bare_ndk__class<"android/view/MotionEvent">(jni));

  return type.get_static_field<int32_t>(name).get();
}

static js_value_t *
bare_ndk_motion_event_obtain(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 6;
  js_value_t *argv[6];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 6);

  int64_t down_time, event_time;

  err = js_get_value_int64(env, argv[0], &down_time);
  assert(err == 0);

  err = js_get_value_int64(env, argv[1], &event_time);
  assert(err == 0);

  int32_t action, meta_state;

  err = js_get_value(env, js_number_t(argv[2]), action);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[5]), meta_state);
  assert(err == 0);

  double x, y;

  err = js_get_value(env, js_number_t(argv[3]), x);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[4]), y);
  assert(err == 0);

  JNIEnv *jni = bare_jni_env();

  auto type = java_class_t<"android/view/MotionEvent">(jni, bare_ndk__class<"android/view/MotionEvent">(jni));

  auto event = type.get_static_method<java_object_t<"android/view/MotionEvent">(int64_t, int64_t, int32_t, float, float, int32_t)>("obtain")(
    down_time, event_time, action, static_cast<float>(x), static_cast<float>(y), meta_state
  );

  return bare_ndk__tag(env, state, event);
}

static js_value_t *
bare_ndk_motion_event_recycle(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/view/MotionEvent"> event;
  err = bare_ndk__read_object(env, state, argv[0], "event", &event);
  if (err < 0) return nullptr;

  event.get_class().get_method<void()>("recycle")(event);

  return nullptr;
}

static js_value_t *
bare_ndk_motion_event_action(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/view/MotionEvent"> event;
  err = bare_ndk__read_object(env, state, argv[0], "event", &event);
  if (err < 0) return nullptr;

  js_value_t *result;
  err = js_create_int32(env, event.get_class().get_method<int32_t()>("getAction")(event), &result);
  assert(err == 0);

  return result;
}

template <java_string_literal_t name>
static js_value_t *
bare_ndk__motion_event_float(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/view/MotionEvent"> event;
  err = bare_ndk__read_object(env, state, argv[0], "event", &event);
  if (err < 0) return nullptr;

  js_value_t *result;
  err = js_create_double(env, event.get_class().get_method<float()>(name)(event), &result);
  assert(err == 0);

  return result;
}

template <java_string_literal_t name>
static js_value_t *
bare_ndk__motion_event_time(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/view/MotionEvent"> event;
  err = bare_ndk__read_object(env, state, argv[0], "event", &event);
  if (err < 0) return nullptr;

  js_value_t *result;
  err = js_create_int64(env, event.get_class().get_method<int64_t()>(name)(event), &result);
  assert(err == 0);

  return result;
}
