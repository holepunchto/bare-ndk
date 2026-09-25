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
