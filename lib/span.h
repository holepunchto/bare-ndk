#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

static js_value_t *
bare_ndk_foreground_color_span_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  int32_t color;
  err = js_get_value(env, js_number_t(argv[0]), color);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  auto init = java_class_t<"android/text/style/ForegroundColorSpan">(jni, bare_ndk__class<"android/text/style/ForegroundColorSpan">(jni));

  return bare_ndk__tag(env, init(color));
}

static js_value_t *
bare_ndk_absolute_size_span_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  int32_t size;
  err = js_get_value(env, js_number_t(argv[0]), size);
  assert(err == 0);

  bool dip;
  err = js_get_value(env, js_boolean_t(argv[1]), dip);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  auto init = java_class_t<"android/text/style/AbsoluteSizeSpan">(jni, bare_ndk__class<"android/text/style/AbsoluteSizeSpan">(jni));

  return bare_ndk__tag(env, init(size, dip));
}

static js_value_t *
bare_ndk_typeface_span_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/graphics/Typeface"> typeface;
  err = bare_ndk__read_object(env, argv[0], "typeface", &typeface);
  if (err < 0) return nullptr;

  JNIEnv *jni = bare_jni__env();

  auto init = java_class_t<"android/text/style/TypefaceSpan">(jni, bare_ndk__class<"android/text/style/TypefaceSpan">(jni));

  return bare_ndk__tag(env, init(typeface));
}
