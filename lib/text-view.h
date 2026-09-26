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

  assert(argc == 1 || argc == 2);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  JNIEnv *jni = bare_jni__env();

  // What a text view holds is a `CharSequence`, and what a caller wants back
  // is the text of it.
  if (argc == 1) {
    auto text = view.get_class().get_method<java_object_t<"java/lang/CharSequence">()>("getText")(view);

    auto string = text.get_class().get_method<std::string()>("toString")(text);

    js_string_t result;
    err = js_create_string(env, string, result);
    assert(err == 0);

    return static_cast<js_value_t *>(result);
  }

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

// The other end of the same thing: a multiplier of one and nothing added is
// the font's own spacing, which is how the property is put back.
static js_value_t *
bare_ndk_text_view_line_spacing(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  double add, multiplier;

  err = js_get_value(env, js_number_t(argv[1]), add);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[2]), multiplier);
  assert(err == 0);

  view.get_class().get_method<void(float, float)>("setLineSpacing")(
    view, static_cast<float>(add), static_cast<float>(multiplier)
  );

  return nullptr;
}

// Android asks for a line height in pixels and has no way to be told to go
// back to the font's own, so putting the property back is a line of exactly
// the height the paint draws, which is what it would have used.
static js_value_t *
bare_ndk_text_view_line_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  auto type = view.get_class();

  double height;
  err = js_get_value(env, js_number_t(argv[1]), height);
  assert(err == 0);

  type.get_method<void(int32_t)>("setLineHeight")(view, static_cast<int32_t>(height));

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

static js_value_t *
bare_ndk_text_view_max_lines(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/widget/TextView"> view;
  err = bare_ndk__read_object(env, argv[0], "textView", &view);
  if (err < 0) return nullptr;

  int32_t lines;
  err = js_get_value(env, js_number_t(argv[1]), lines);
  assert(err == 0);

  view.get_class().get_method<void(int32_t)>("setMaxLines")(view, lines);

  return nullptr;
}

// Where the text is cut, named by the constant rather than numbered, and null
// for a view that cuts without saying so.
static js_value_t *
bare_ndk_text_view_ellipsize(js_env_t *env, js_callback_info_t *info) {
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

  auto set = view.get_class().get_method<void(java_object_t<"android/text/TextUtils$TruncateAt">)>("setEllipsize");

  js_value_type_t type;
  err = js_typeof(env, argv[1], &type);
  assert(err == 0);

  if (type == js_null) {
    set(view, java_object_t<"android/text/TextUtils$TruncateAt">());
  } else {
    std::string name;
    err = js_get_value(env, js_string_t(argv[1]), name);
    assert(err == 0);

    auto truncations = java_class_t<"android/text/TextUtils$TruncateAt">(jni, bare_ndk__class<"android/text/TextUtils$TruncateAt">(jni));

    set(view, truncations.get_static_field<java_object_t<"android/text/TextUtils$TruncateAt">>(name).get());
  }

  return nullptr;
}
