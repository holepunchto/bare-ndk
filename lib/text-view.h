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
bare_ndk_text_view_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"android/widget/TextView">(jni, bare_ndk__class<"android/widget/TextView">(jni));

  return bare_ndk__tag(env, init(context));
}

static js_value_t *
bare_ndk_text_view_text(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  JNIEnv *jni = bare_jni__env();

  // `setText` takes a `CharSequence`, which a plain string is and a span
  // builder is, so both arrive here.
  bool is_string;
  err = js_is_string(env, argv[1], &is_string);
  assert(err == 0);

  auto setText = view.get_class().get_method<void(java_object_t<"java/lang/CharSequence">)>("setText");

  if (is_string) {
    std::string text;
    err = js_get_value(env, js_string_t(argv[1]), text);
    assert(err == 0);

    setText(view, java_object_t<"java/lang/CharSequence">(jni, java_string_t(jni, text)));
  } else {
    java_object_t<"java/lang/CharSequence"> text;
    err = bare_ndk__read_object(env, argv[1], "text", &text);
    if (err < 0) return nullptr;

    setText(view, text);
  }

  return nullptr;
}

static js_value_t *
bare_ndk_text_view_text_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  auto type = view.get_class();

  if (argc == 1) {
    js_value_t *result;
    err = js_create_double(env, type.get_method<float()>("getTextSize")(view), &result);
    assert(err == 0);

    return result;
  }

  double size;
  err = js_get_value(env, js_number_t(argv[1]), size);
  assert(err == 0);

  // In pixels, like every other length here, and like the view that measured it.
  type.get_method<void(int32_t, float)>("setTextSize")(view, 0, static_cast<float>(size));

  return nullptr;
}

static js_value_t *
bare_ndk_text_view_text_color(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  auto type = view.get_class();

  if (argc == 1) {
    js_value_t *result;
    err = js_create_int32(env, type.get_method<int32_t()>("getCurrentTextColor")(view), &result);
    assert(err == 0);

    return result;
  }

  int32_t color;
  err = js_get_value(env, js_number_t(argv[1]), color);
  assert(err == 0);

  type.get_method<void(int32_t)>("setTextColor")(view, color);

  return nullptr;
}

static js_value_t *
bare_ndk_text_view_typeface(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  auto type = view.get_class();

  if (argc == 1) {
    return bare_ndk__tag(env, type.get_method<java_object_t<"android/graphics/Typeface">()>("getTypeface")(view));
  }

  java_object_t<"android/graphics/Typeface"> typeface;
  err = bare_ndk__read_object(env, argv[1], "typeface", &typeface);
  if (err < 0) return nullptr;

  type.get_method<void(java_object_t<"android/graphics/Typeface">)>("setTypeface")(view, typeface);

  return nullptr;
}

static js_value_t *
bare_ndk_text_view_gravity(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  int32_t gravity;
  err = js_get_value(env, js_number_t(argv[1]), gravity);
  assert(err == 0);

  view.get_class().get_method<void(int32_t)>("setGravity")(view, gravity);

  return nullptr;
}

static js_value_t *
bare_ndk_text_view_justification_mode(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  int32_t mode;
  err = js_get_value(env, js_number_t(argv[1]), mode);
  assert(err == 0);

  view.get_class().get_method<void(int32_t)>("setJustificationMode")(view, mode);

  return nullptr;
}
