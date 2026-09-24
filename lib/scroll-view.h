#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "activity.h"
#include "bridging.h"

enum {
  bare_ndk_scroll_view_event_scroll = 1 << 0,
};

static void
bare_ndk_scroll_group__on_scroll(java_env_t env, java_object_t<"to/holepunch/bare/ndk/ScrollGroup"> receiver, int32_t x, int32_t y) {
  bare_ndk__emit(receiver, "scroll", 2, (const double[]) {static_cast<double>(x), static_cast<double>(y)});
}

static void
bare_ndk_horizontal_scroll_group__on_scroll(java_env_t env, java_object_t<"to/holepunch/bare/ndk/HorizontalScrollGroup"> receiver, int32_t x, int32_t y) {
  bare_ndk__emit(receiver, "scroll", 2, (const double[]) {static_cast<double>(x), static_cast<double>(y)});
}

static void
bare_ndk_scroll_view_register(JNIEnv *jni) {
  java_class_t<"to/holepunch/bare/ndk/ScrollGroup">(jni, bare_ndk__class<"to/holepunch/bare/ndk/ScrollGroup">(jni))
    .register_natives(java_native_method_t<bare_ndk_scroll_group__on_scroll>("onScroll"));

  java_class_t<"to/holepunch/bare/ndk/HorizontalScrollGroup">(jni, bare_ndk__class<"to/holepunch/bare/ndk/HorizontalScrollGroup">(jni))
    .register_natives(java_native_method_t<bare_ndk_horizontal_scroll_group__on_scroll>("onScroll"));
}

static js_value_t *
bare_ndk_scroll_view_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"to/holepunch/bare/ndk/ScrollGroup">(jni, bare_ndk__class<"to/holepunch/bare/ndk/ScrollGroup">(jni));

  return bare_ndk__tag(env, init(context));
}

static js_value_t *
bare_ndk_scroll_view_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  int32_t mask;
  err = js_get_value(env, js_number_t(argv[1]), mask);
  assert(err == 0);

  view.get_class().get_method<void(int32_t)>("setEvents")(view, mask);

  return nullptr;
}

// `ScrollView` scrolls vertically and `HorizontalScrollView` horizontally, and
// neither does the other, so the axis is chosen when the view is made rather
// than set on it.
static js_value_t *
bare_ndk_horizontal_scroll_view_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"to/holepunch/bare/ndk/HorizontalScrollGroup">(jni, bare_ndk__class<"to/holepunch/bare/ndk/HorizontalScrollGroup">(jni));

  return bare_ndk__tag(env, init(context));
}
