#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <string>

#include "activity.h"
#include "bridging.h"

static js_value_t *
bare_ndk_image_view_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"android/widget/ImageView">(jni, bare_ndk__class<"android/widget/ImageView">(jni));

  return bare_ndk__tag(env, init(context));
}

static js_value_t *
bare_ndk_image_view_set_image_bitmap(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/widget/ImageView"> view;
  err = bare_ndk__read_object(env, argv[0], "imageView", &view);
  if (err < 0) return nullptr;

  java_object_t<"android/graphics/Bitmap"> bitmap;

  js_value_type_t type;
  err = js_typeof(env, argv[1], &type);
  assert(err == 0);

  if (type != js_null) {
    err = bare_ndk__read_object(env, argv[1], "bitmap", &bitmap);
    if (err < 0) return nullptr;
  }

  view.get_class().get_method<void(java_object_t<"android/graphics/Bitmap">)>("setImageBitmap")(view, bitmap);

  return nullptr;
}

// `ScaleType` is a Java enum, so what crosses is the constant's own name and
// the field it stands for is read back here.
static js_value_t *
bare_ndk_image_view_scale_type(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"android/widget/ImageView"> view;
  err = bare_ndk__read_object(env, argv[0], "imageView", &view);
  if (err < 0) return nullptr;

  JNIEnv *jni = bare_jni__env();

  if (argc == 1) {
    auto get = view.get_class().get_method<java_object_t<"android/widget/ImageView$ScaleType">()>("getScaleType");

    auto value = get(view);

    js_string_t name;
    err = js_create_string(env, value.get_class().get_method<std::string()>("name")(value), name);
    assert(err == 0);

    return static_cast<js_value_t *>(name);
  }

  std::string name;
  err = js_get_value(env, js_string_t(argv[1]), name);
  assert(err == 0);

  auto scale_types = java_class_t<"android/widget/ImageView$ScaleType">(jni, bare_ndk__class<"android/widget/ImageView$ScaleType">(jni));

  auto constant = scale_types.get_static_field<java_object_t<"android/widget/ImageView$ScaleType">>(name).get();

  view.get_class().get_method<void(java_object_t<"android/widget/ImageView$ScaleType">)>("setScaleType")(view, constant);

  return nullptr;
}
