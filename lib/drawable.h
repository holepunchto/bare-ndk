#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "activity.h"
#include "bridging.h"

static js_value_t *
bare_ndk_gradient_drawable_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto init = java_class_t<"android/graphics/drawable/GradientDrawable">(jni, bare_ndk__class<"android/graphics/drawable/GradientDrawable">(jni));

  return bare_ndk__tag(env, init());
}

static js_value_t *
bare_ndk_gradient_drawable_color(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/graphics/drawable/GradientDrawable"> drawable;
  err = bare_ndk__read_object(env, argv[0], "drawable", &drawable);
  if (err < 0) return nullptr;

  int32_t color;
  err = js_get_value(env, js_number_t(argv[1]), color);
  assert(err == 0);

  drawable.get_class().get_method<void(int32_t)>("setColor")(drawable, color);

  return nullptr;
}

static js_value_t *
bare_ndk_gradient_drawable_corner_radius(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/graphics/drawable/GradientDrawable"> drawable;
  err = bare_ndk__read_object(env, argv[0], "drawable", &drawable);
  if (err < 0) return nullptr;

  double radius;
  err = js_get_value(env, js_number_t(argv[1]), radius);
  assert(err == 0);

  drawable.get_class().get_method<void(float)>("setCornerRadius")(drawable, static_cast<float>(radius));

  return nullptr;
}

static js_value_t *
bare_ndk_gradient_drawable_stroke(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  java_object_t<"android/graphics/drawable/GradientDrawable"> drawable;
  err = bare_ndk__read_object(env, argv[0], "drawable", &drawable);
  if (err < 0) return nullptr;

  int32_t width, color;

  err = js_get_value(env, js_number_t(argv[1]), width);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[2]), color);
  assert(err == 0);

  drawable.get_class().get_method<void(int32_t, int32_t)>("setStroke")(drawable, width, color);

  return nullptr;
}
