#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <string>

#include "bridging.h"

static js_value_t *
bare_ndk_bitmap_factory_decode_file(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  std::string path;
  err = js_get_value(env, js_string_t(argv[0]), path);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  auto factory = java_class_t<"android/graphics/BitmapFactory">(jni, bare_ndk__class<"android/graphics/BitmapFactory">(jni));

  auto decode = factory.get_static_method<java_object_t<"android/graphics/Bitmap">(std::string)>("decodeFile");

  auto bitmap = decode(path);

  // A file that is missing or is not an image decodes to null rather than
  // raising, which is how a caller is told it cannot be drawn.
  if (static_cast<jobject>(bitmap) == nullptr) {
    js_value_t *result;
    err = js_get_null(env, &result);
    assert(err == 0);

    return result;
  }

  return bare_ndk__tag(env, bitmap);
}

static js_value_t *
bare_ndk_bitmap_width(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/graphics/Bitmap"> bitmap;
  err = bare_ndk__read_object(env, argv[0], "bitmap", &bitmap);
  if (err < 0) return nullptr;

  js_value_t *result;
  err = js_create_int32(env, bitmap.get_class().get_method<int32_t()>("getWidth")(bitmap), &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_ndk_bitmap_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/graphics/Bitmap"> bitmap;
  err = bare_ndk__read_object(env, argv[0], "bitmap", &bitmap);
  if (err < 0) return nullptr;

  js_value_t *result;
  err = js_create_int32(env, bitmap.get_class().get_method<int32_t()>("getHeight")(bitmap), &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_ndk_bitmap_density(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"android/graphics/Bitmap"> bitmap;
  err = bare_ndk__read_object(env, argv[0], "bitmap", &bitmap);
  if (err < 0) return nullptr;

  auto type = bitmap.get_class();

  if (argc == 1) {
    js_value_t *result;
    err = js_create_int32(env, type.get_method<int32_t()>("getDensity")(bitmap), &result);
    assert(err == 0);

    return result;
  }

  int32_t density;
  err = js_get_value(env, js_number_t(argv[1]), density);
  assert(err == 0);

  type.get_method<void(int32_t)>("setDensity")(bitmap, density);

  return nullptr;
}
