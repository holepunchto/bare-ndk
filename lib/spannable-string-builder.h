#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <string>

#include "bridging.h"

static js_value_t *
bare_ndk_spannable_string_builder_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto init = java_class_t<"android/text/SpannableStringBuilder">(jni, bare_ndk__class<"android/text/SpannableStringBuilder">(jni));

  return bare_ndk__tag(env, init());
}

static js_value_t *
bare_ndk_spannable_string_builder_append(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/text/SpannableStringBuilder"> builder;
  err = bare_ndk__read_object(env, argv[0], "builder", &builder);
  if (err < 0) return nullptr;

  std::string text;
  err = js_get_value(env, js_string_t(argv[1]), text);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  auto string = java_string_t(jni, text);

  builder.get_class()
    .get_method<java_object_t<"android/text/SpannableStringBuilder">(java_object_t<"java/lang/CharSequence">)>("append")(
      builder, java_object_t<"java/lang/CharSequence">(jni, string)
    );

  return nullptr;
}

static js_value_t *
bare_ndk_spannable_string_builder_length(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/text/SpannableStringBuilder"> builder;
  err = bare_ndk__read_object(env, argv[0], "builder", &builder);
  if (err < 0) return nullptr;

  int32_t length = builder.get_class().get_method<int32_t()>("length")(builder);

  js_value_t *result;
  err = js_create_int32(env, length, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_ndk_spannable_string_builder_set_span(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 5);

  java_object_t<"android/text/SpannableStringBuilder"> builder;
  err = bare_ndk__read_object(env, argv[0], "builder", &builder);
  if (err < 0) return nullptr;

  java_object_t<"java/lang/Object"> span;
  err = bare_ndk__read_object(env, argv[1], "span", &span);
  if (err < 0) return nullptr;

  int32_t start, end, flags;

  err = js_get_value(env, js_number_t(argv[2]), start);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[3]), end);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[4]), flags);
  assert(err == 0);

  builder.get_class()
    .get_method<void(java_object_t<"java/lang/Object">, int32_t, int32_t, int32_t)>("setSpan")(
      builder, span, start, end, flags
    );

  return nullptr;
}
