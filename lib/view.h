#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

static js_value_t *
bare_ndk_view_background_color(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  int32_t color;
  err = js_get_value(env, js_number_t(argv[1]), color);
  assert(err == 0);

  auto set_background_color = view.get_class().get_method<void(int32_t)>("setBackgroundColor");

  set_background_color(view, color);

  return nullptr;
}

static js_value_t *
bare_ndk_view_scroll_x(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  js_value_t *result;
  err = js_create_int32(env, view.get_class().get_method<int32_t()>("getScrollX")(view), &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_ndk_view_scroll_y(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  js_value_t *result;
  err = js_create_int32(env, view.get_class().get_method<int32_t()>("getScrollY")(view), &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_ndk_view_scroll_to(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  int32_t x, y;

  err = js_get_value(env, js_number_t(argv[1]), x);
  assert(err == 0);

  err = js_get_value(env, js_number_t(argv[2]), y);
  assert(err == 0);

  view.get_class().get_method<void(int32_t, int32_t)>("scrollTo")(view, x, y);

  return nullptr;
}

static js_value_t *
bare_ndk_view_width(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  auto get_width = view.get_class().get_method<int32_t()>("getWidth");

  js_value_t *result;
  err = js_create_int32(env, get_width(view), &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_ndk_view_height(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  auto get_height = view.get_class().get_method<int32_t()>("getHeight");

  js_value_t *result;
  err = js_create_int32(env, get_height(view), &result);
  assert(err == 0);

  return result;
}

// Invisible rather than gone, because the box a view was given is the
// layout's and a gone view is not laid out at all.
// The highlight Android draws over a view that has the focus and says nothing
// about focus itself, which is every view whose background carries no focused
// state.
static js_value_t *
bare_ndk_view_default_focus_highlight(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  bool enabled;
  err = js_get_value(env, js_boolean_t(argv[1]), enabled);
  assert(err == 0);

  view.get_class().get_method<void(bool)>("setDefaultFocusHighlightEnabled")(view, enabled);

  return nullptr;
}

static js_value_t *
bare_ndk_view_visible(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  bool visible;
  err = js_get_value(env, js_boolean_t(argv[1]), visible);
  assert(err == 0);

  view.get_class().get_method<void(int32_t)>("setVisibility")(view, visible ? 0 : 4);

  return nullptr;
}

static js_value_t *
bare_ndk_view_alpha(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  double alpha;
  err = js_get_value(env, js_number_t(argv[1]), alpha);
  assert(err == 0);

  view.get_class().get_method<void(float)>("setAlpha")(view, static_cast<float>(alpha));

  return nullptr;
}

static js_value_t *
bare_ndk_view_clip_to_outline(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  bool clip;
  err = js_get_value(env, js_boolean_t(argv[1]), clip);
  assert(err == 0);

  view.get_class().get_method<void(bool)>("setClipToOutline")(view, clip);

  return nullptr;
}

static js_value_t *
bare_ndk_view_background(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  java_object_t<"android/graphics/drawable/Drawable"> drawable;
  err = bare_ndk__read_object(env, argv[1], "drawable", &drawable);
  if (err < 0) return nullptr;

  view.get_class().get_method<void(java_object_t<"android/graphics/drawable/Drawable">)>("setBackground")(view, drawable);

  return nullptr;
}

// Null until the view is attached to a window.
static js_value_t *
bare_ndk_view_root_window_insets(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  auto get_insets = view.get_class().get_method<java_object_t<"android/view/WindowInsets">()>("getRootWindowInsets");

  auto insets = get_insets(view);

  if (static_cast<jobject>(insets) == nullptr) {
    js_value_t *result;
    err = js_get_null(env, &result);
    assert(err == 0);

    return result;
  }

  return bare_ndk__tag(env, insets);
}

static js_value_t *
bare_ndk_view_enabled(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  auto type = view.get_class();

  if (argc == 1) {
    js_value_t *result;
    err = js_get_boolean(env, type.get_method<bool()>("isEnabled")(view), &result);
    assert(err == 0);

    return result;
  }

  bool enabled;
  err = js_get_value(env, js_boolean_t(argv[1]), enabled);
  assert(err == 0);

  type.get_method<void(bool)>("setEnabled")(view, enabled);

  return nullptr;
}

static js_value_t *
bare_ndk_view_set_padding(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 5);

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[0], "view", &view);
  if (err < 0) return nullptr;

  int32_t left;
  err = js_get_value(env, js_number_t(argv[1]), left);
  assert(err == 0);

  int32_t top;
  err = js_get_value(env, js_number_t(argv[2]), top);
  assert(err == 0);

  int32_t right;
  err = js_get_value(env, js_number_t(argv[3]), right);
  assert(err == 0);

  int32_t bottom;
  err = js_get_value(env, js_number_t(argv[4]), bottom);
  assert(err == 0);

  view.get_class().get_method<void(int32_t, int32_t, int32_t, int32_t)>("setPadding")(view, left, top, right, bottom);

  return nullptr;
}

// A `View` composes its own transform out of these rather than taking a
// matrix, because a matrix handed to one through `setAnimationMatrix` is
// drawn through and never hit tested: the view would be touched where it is
// not drawn.
#define V(name, method) \
  static js_value_t * \
  bare_ndk_view_##name(js_env_t *env, js_callback_info_t *info) { \
    int err; \
\
    size_t argc = 2; \
    js_value_t *argv[2]; \
\
    err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr); \
    assert(err == 0); \
\
    assert(argc == 2); \
\
    java_object_t<"android/view/View"> view; \
    err = bare_ndk__read_object(env, argv[0], "view", &view); \
    if (err < 0) return nullptr; \
\
    double value; \
    err = js_get_value(env, js_number_t(argv[1]), value); \
    assert(err == 0); \
\
    view.get_class().get_method<void(float)>(method)(view, static_cast<float>(value)); \
\
    return nullptr; \
  }

V(translation_x, "setTranslationX")
V(translation_y, "setTranslationY")
V(translation_z, "setTranslationZ")
V(scale_x, "setScaleX")
V(scale_y, "setScaleY")
V(rotation, "setRotation")
V(rotation_x, "setRotationX")
V(rotation_y, "setRotationY")
V(pivot_x, "setPivotX")
V(pivot_y, "setPivotY")
V(camera_distance, "setCameraDistance")
V(elevation, "setElevation")
#undef V

// The colours of the two lights a raised `View` casts its shadow by. Android
// packs a colour into the 32 bits of a signed integer, as a background does.
#define V(name, method) \
  static js_value_t * \
  bare_ndk_view_##name(js_env_t *env, js_callback_info_t *info) { \
    int err; \
\
    size_t argc = 2; \
    js_value_t *argv[2]; \
\
    err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr); \
    assert(err == 0); \
\
    assert(argc == 2); \
\
    java_object_t<"android/view/View"> view; \
    err = bare_ndk__read_object(env, argv[0], "view", &view); \
    if (err < 0) return nullptr; \
\
    int32_t value; \
    err = js_get_value(env, js_number_t(argv[1]), value); \
    assert(err == 0); \
\
    view.get_class().get_method<void(int32_t)>(method)(view, value); \
\
    return nullptr; \
  }

V(outline_ambient_shadow_color, "setOutlineAmbientShadowColor")
V(outline_spot_shadow_color, "setOutlineSpotShadowColor")
#undef V
