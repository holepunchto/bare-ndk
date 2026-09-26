#pragma once

#include <vector>

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

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3 || argc == 5);

  java_object_t<"android/graphics/drawable/GradientDrawable"> drawable;
  err = bare_ndk__read_object(env, argv[0], "drawable", &drawable);
  if (err < 0) return nullptr;

  int32_t width, color;

  err = js_get_value(env, js_number_t(argv[1]), width);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[2]), color);
  assert(err == 0);

  if (argc == 3) {
    drawable.get_class().get_method<void(int32_t, int32_t)>("setStroke")(drawable, width, color);

    return nullptr;
  }

  double dash_width, dash_gap;

  err = js_get_value(env, js_number_t(argv[3]), dash_width);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[4]), dash_gap);
  assert(err == 0);

  drawable.get_class().get_method<void(int32_t, int32_t, float, float)>("setStroke")(drawable, width, color, static_cast<float>(dash_width), static_cast<float>(dash_gap));

  return nullptr;
}

static js_value_t *
bare_ndk_gradient_drawable_corner_radii(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/graphics/drawable/GradientDrawable"> drawable;
  err = bare_ndk__read_object(env, argv[0], "drawable", &drawable);
  if (err < 0) return nullptr;

  uint32_t len;
  err = js_get_array_length(env, argv[1], &len);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  std::vector<float> values(len);

  for (uint32_t i = 0; i < len; i++) {
    js_value_t *element;
    err = js_get_element(env, argv[1], i, &element);
    assert(err == 0);

    double radius;
    err = js_get_value_double(env, element, &radius);
    assert(err == 0);

    values[i] = static_cast<float>(radius);
  }

  java_array_t<float> radii(jni, len);

  // Copied rather than written through, because writing through pins the
  // elements and JNI is free to hand back a copy of them: what was written
  // would then reach Java only when the pin was released, which is after the
  // call that needed it.
  radii.copy_from(values);

  drawable.get_class().get_method<void(java_array_t<float>)>("setCornerRadii")(drawable, radii);

  return nullptr;
}
