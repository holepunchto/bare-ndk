#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <string>

#include "bridging.h"

static js_value_t *
bare_ndk_typeface_create(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  std::string family;
  err = js_get_value(env, js_string_t(argv[0]), family);
  assert(err == 0);

  int32_t style;
  err = js_get_value(env, js_number_t(argv[1]), style);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  auto typefaces = java_class_t<"android/graphics/Typeface">(jni, bare_ndk__class<"android/graphics/Typeface">(jni));

  auto create = typefaces.get_static_method<java_object_t<"android/graphics/Typeface">(std::string, int32_t)>("create");

  return bare_ndk__tag(env, create(family, style));
}

static js_value_t *
bare_ndk_typeface_create_from_typeface(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  java_object_t<"android/graphics/Typeface"> family;
  err = bare_ndk__read_object(env, argv[0], "family", &family);
  if (err < 0) return nullptr;

  int32_t weight;
  err = js_get_value(env, js_number_t(argv[1]), weight);
  assert(err == 0);

  bool italic;
  err = js_get_value(env, js_boolean_t(argv[2]), italic);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  auto typefaces = java_class_t<"android/graphics/Typeface">(jni, bare_ndk__class<"android/graphics/Typeface">(jni));

  auto create = typefaces.get_static_method<java_object_t<"android/graphics/Typeface">(java_object_t<"android/graphics/Typeface">, int32_t, bool)>("create");

  return bare_ndk__tag(env, create(family, weight, italic));
}
