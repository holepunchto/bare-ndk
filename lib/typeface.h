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
