#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "activity.h"
#include "bridging.h"

static js_value_t *
bare_ndk_progress_bar_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"android/widget/ProgressBar">(jni, bare_ndk__class<"android/widget/ProgressBar">(jni));

  return bare_ndk__tag(env, init(context));
}

static js_value_t *
bare_ndk_progress_bar_indeterminate(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/widget/ProgressBar"> bar;
  err = bare_ndk__read_object(env, argv[0], "progressBar", &bar);
  if (err < 0) return nullptr;

  bool indeterminate;
  err = js_get_value(env, js_boolean_t(argv[1]), indeterminate);
  assert(err == 0);

  bar.get_class().get_method<void(bool)>("setIndeterminate")(bar, indeterminate);

  return nullptr;
}

// A tint is a state list rather than a colour, because Android lets a widget
// draw differently depending on what it is doing.
static js_value_t *
bare_ndk_progress_bar_indeterminate_tint(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  JNIEnv *jni = bare_jni__env();

  java_object_t<"android/widget/ProgressBar"> bar;
  err = bare_ndk__read_object(env, argv[0], "progressBar", &bar);
  if (err < 0) return nullptr;

  int32_t color;
  err = js_get_value(env, js_number_t(argv[1]), color);
  assert(err == 0);

  auto list = java_class_t<"android/content/res/ColorStateList">(jni, bare_ndk__class<"android/content/res/ColorStateList">(jni));

  auto tint = list.get_static_method<java_object_t<"android/content/res/ColorStateList">(int32_t)>("valueOf")(color);

  bar.get_class().get_method<void(java_object_t<"android/content/res/ColorStateList">)>("setIndeterminateTintList")(bar, tint);

  return nullptr;
}
