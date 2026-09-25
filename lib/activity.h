#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <android/native_activity.h>

#include "bridging.h"

extern ANativeActivity *bare_native_activity;

static js_value_t *
bare_ndk_activity_init(js_env_t *env, js_callback_info_t *info) {
  auto activity = java_object_t<"android/app/Activity">(bare_jni__env(), bare_native_activity->clazz);

  return bare_ndk__tag(env, activity);
}

static js_value_t *
bare_ndk_activity_content_view(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/app/Activity"> activity;
  err = bare_ndk__read_object(env, argv[0], "activity", &activity);
  if (err < 0) return nullptr;

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[1], "view", &view);
  if (err < 0) return nullptr;

  auto set_content_view = activity.get_class().get_method<void(java_object_t<"android/view/View">)>("setContentView");

  set_content_view(activity, view);

  return nullptr;
}

static js_value_t *
bare_ndk_activity_resources(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/app/Activity"> activity;
  err = bare_ndk__read_object(env, argv[0], "activity", &activity);
  if (err < 0) return nullptr;

  auto get_resources = activity.get_class().get_method<java_object_t<"android/content/res/Resources">()>("getResources");

  return bare_ndk__tag(env, get_resources(activity));
}

// A colour the theme decides rather than the caller, which is how a widget
// draws itself in the accent the person running it chose.
static js_value_t *
bare_ndk_activity_theme_color(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  JNIEnv *jni = bare_jni__env();

  std::string name;
  err = js_get_value(env, js_string_t(argv[0]), name);
  assert(err == 0);

  // The attribute's own number, read off the platform's `R` rather than
  // written down here, where a wrong one would quietly resolve to some other
  // attribute entirely.
  auto attributes = java_class_t<"android/R$attr">(jni, bare_ndk__class<"android/R$attr">(jni));

  auto attribute = attributes.get_static_field<int32_t>(name).get();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto theme = context.get_class().get_method<java_object_t<"android/content/res/Resources$Theme">()>("getTheme")(context);

  auto init = java_class_t<"android/util/TypedValue">(jni, bare_ndk__class<"android/util/TypedValue">(jni));

  auto value = init();

  theme.get_class().get_method<bool(int32_t, java_object_t<"android/util/TypedValue">, bool)>("resolveAttribute")(theme, attribute, value, true);

  js_value_t *result;
  err = js_create_int32(env, value.get(value.get_class().get_field<int32_t>("data")), &result);
  assert(err == 0);

  return result;
}
