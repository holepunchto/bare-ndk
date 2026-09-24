#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "activity.h"
#include "bridging.h"

// Called by Android rather than by the runtime, so it is registered onto the
// Java class instead of exported. The registry resolves the receiver back to
// the wrapper listening for it.
static void
bare_ndk_frame_group__on_resize(java_env_t env, java_object_t<"to/holepunch/bare/ndk/FrameGroup"> receiver, int32_t width, int32_t height) {
  bare_ndk__emit(receiver, "resize", 2, (const double[]) {static_cast<double>(width), static_cast<double>(height)});
}

static void
bare_ndk_frame_group_register(JNIEnv *jni) {
  java_class_t<"to/holepunch/bare/ndk/FrameGroup">(jni, bare_ndk__class<"to/holepunch/bare/ndk/FrameGroup">(jni))
    .register_natives(java_native_method_t<bare_ndk_frame_group__on_resize>("onResize"));
}

static js_value_t *
bare_ndk_frame_group_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"to/holepunch/bare/ndk/FrameGroup">(jni, bare_ndk__class<"to/holepunch/bare/ndk/FrameGroup">(jni));

  auto group = init(context);

  return bare_ndk__tag(env, group);
}

static js_value_t *
bare_ndk_frame_group_set_frame(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 6;
  js_value_t *argv[6];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 6);

  java_object_t<"to/holepunch/bare/ndk/FrameGroup"> group;
  err = bare_ndk__read_object(env, argv[0], "group", &group);
  if (err < 0) return nullptr;

  java_object_t<"android/view/View"> child;
  err = bare_ndk__read_object(env, argv[1], "child", &child);
  if (err < 0) return nullptr;

  int32_t x, y, width, height;

  err = js_get_value(env, js_number_t(argv[2]), x);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[3]), y);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[4]), width);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[5]), height);
  assert(err == 0);

  auto set_frame = group.get_class().get_method<void(java_object_t<"android/view/View">, int32_t, int32_t, int32_t, int32_t)>("setFrame");

  set_frame(group, child, x, y, width, height);

  return nullptr;
}

static js_value_t *
bare_ndk_frame_group_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"to/holepunch/bare/ndk/FrameGroup"> group;
  err = bare_ndk__read_object(env, argv[0], "group", &group);
  if (err < 0) return nullptr;

  int32_t mask;
  err = js_get_value(env, js_number_t(argv[1]), mask);
  assert(err == 0);

  auto set_events = group.get_class().get_method<void(int32_t)>("setEvents");

  set_events(group, mask);

  return nullptr;
}
