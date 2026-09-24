#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <cmath>
#include <string>

#include "activity.h"
#include "bridging.h"

// Pixels rather than scaled pixels, because every other length here is.
static const int32_t bare_ndk__unit_px = 0;

// `View.MeasureSpec` packs a mode into the top two bits of a size, and an
// unspecified axis is a zero mode, so it is simply a zero spec.
static const int32_t bare_ndk__measure_at_most = 2 << 30;

static jobject bare_ndk__measured = nullptr;
static jobject bare_ndk__typeface = nullptr;
static float bare_ndk__text_size = 0;

// Measuring through the control that draws resolves the same defaults it will,
// which is why this is a `TextView` and not a `Paint` and a `StaticLayout`.
static java_object_t<"android/widget/TextView">
bare_ndk__measuring_view(JNIEnv *jni) {
  if (bare_ndk__measured == nullptr) {
    auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

    auto init = java_class_t<"android/widget/TextView">(jni, bare_ndk__class<"android/widget/TextView">(jni));

    auto view = init(context);

    // `setText` reads the layout parameters, which a view with no parent lacks.
    auto params = java_class_t<"android/view/ViewGroup$LayoutParams">(jni, bare_ndk__class<"android/view/ViewGroup$LayoutParams">(jni));

    view.get_class().get_method<void(java_object_t<"android/view/ViewGroup$LayoutParams">)>("setLayoutParams")(
      view, params(-2, -2)
    );

    bare_ndk__measured = jni->NewGlobalRef(view);

    auto type = view.get_class();

    bare_ndk__text_size = type.get_method<float()>("getTextSize")(view);

    bare_ndk__typeface = jni->NewGlobalRef(
      type.get_method<java_object_t<"android/graphics/Typeface">()>("getTypeface")(view)
    );
  }

  return java_object_t<"android/widget/TextView">(jni, bare_ndk__measured);
}

static js_value_t *
bare_ndk_text_measure(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 4;
  js_value_t *argv[4];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 4);

  std::string text;
  err = js_get_value(env, js_string_t(argv[0]), text);
  assert(err == 0);

  bool has_family;
  err = js_is_string(env, argv[1], &has_family);
  assert(err == 0);

  std::string family;

  if (has_family) {
    err = js_get_value(env, js_string_t(argv[1]), family);
    assert(err == 0);
  }

  double size;
  err = js_get_value(env, js_number_t(argv[2]), size);
  assert(err == 0);

  double width;
  err = js_get_value(env, js_number_t(argv[3]), width);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  auto view = bare_ndk__measuring_view(jni);

  auto type = view.get_class();

  auto string = java_string_t(jni, text);

  type.get_method<void(java_object_t<"java/lang/CharSequence">)>("setText")(
    view, java_object_t<"java/lang/CharSequence">(jni, string)
  );

  // An unset size or family goes back to the control's own.
  type.get_method<void(int32_t, float)>("setTextSize")(
    view, bare_ndk__unit_px, size > 0 ? static_cast<float>(size) : bare_ndk__text_size
  );

  auto typeface = java_object_t<"android/graphics/Typeface">(jni, bare_ndk__typeface);

  if (has_family) {
    auto typefaces = java_class_t<"android/graphics/Typeface">(jni, bare_ndk__class<"android/graphics/Typeface">(jni));

    typeface = typefaces.get_static_method<java_object_t<"android/graphics/Typeface">(std::string, int32_t)>("create")(family, 0);
  }

  type.get_method<void(java_object_t<"android/graphics/Typeface">)>("setTypeface")(view, typeface);

  int32_t spec = std::isfinite(width) ? (static_cast<int32_t>(width) | bare_ndk__measure_at_most) : 0;

  type.get_method<void(int32_t, int32_t)>("measure")(view, spec, 0);

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

  const char *names[] = {"width", "height", "lines"};

  int32_t values[] = {
    type.get_method<int32_t()>("getMeasuredWidth")(view),
    type.get_method<int32_t()>("getMeasuredHeight")(view),
    type.get_method<int32_t()>("getLineCount")(view)
  };

  for (size_t i = 0; i < 3; i++) {
    js_value_t *value;
    err = js_create_int32(env, values[i], &value);
    assert(err == 0);

    err = js_set_named_property(env, result, names[i], value);
    assert(err == 0);
  }

  return result;
}

// Text whose runs carry their own spans is measured the same way, through the
// control that draws it, with the base paint put back to the control's own so
// that only the spans decide.
static js_value_t *
bare_ndk_text_measure_spanned(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"java/lang/CharSequence"> text;
  err = bare_ndk__read_object(env, argv[0], "text", &text);
  if (err < 0) return nullptr;

  double width;
  err = js_get_value(env, js_number_t(argv[1]), width);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  auto view = bare_ndk__measuring_view(jni);

  auto type = view.get_class();

  type.get_method<void(java_object_t<"java/lang/CharSequence">)>("setText")(view, text);

  type.get_method<void(int32_t, float)>("setTextSize")(view, bare_ndk__unit_px, bare_ndk__text_size);

  type.get_method<void(java_object_t<"android/graphics/Typeface">)>("setTypeface")(
    view, java_object_t<"android/graphics/Typeface">(jni, bare_ndk__typeface)
  );

  int32_t spec = std::isfinite(width) ? (static_cast<int32_t>(width) | bare_ndk__measure_at_most) : 0;

  type.get_method<void(int32_t, int32_t)>("measure")(view, spec, 0);

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

  const char *names[] = {"width", "height", "lines"};

  int32_t values[] = {
    type.get_method<int32_t()>("getMeasuredWidth")(view),
    type.get_method<int32_t()>("getMeasuredHeight")(view),
    type.get_method<int32_t()>("getLineCount")(view)
  };

  for (size_t i = 0; i < 3; i++) {
    js_value_t *value;
    err = js_create_int32(env, values[i], &value);
    assert(err == 0);

    err = js_set_named_property(env, result, names[i], value);
    assert(err == 0);
  }

  return result;
}
