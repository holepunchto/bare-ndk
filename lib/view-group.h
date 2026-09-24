#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

static js_value_t *
bare_ndk_view_group_add_view(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 3);

  java_object_t<"android/view/ViewGroup"> group;
  err = bare_ndk__read_object(env, argv[0], "group", &group);
  if (err < 0) return nullptr;

  java_object_t<"android/view/View"> child;
  err = bare_ndk__read_object(env, argv[1], "child", &child);
  if (err < 0) return nullptr;

  int32_t index;
  err = js_get_value(env, js_number_t(argv[2]), index);
  assert(err == 0);

  auto add_view = group.get_class().get_method<void(java_object_t<"android/view/View">, int32_t)>("addView");

  add_view(group, child, index);

  return nullptr;
}

static js_value_t *
bare_ndk_view_group_remove_view(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/ViewGroup"> group;
  err = bare_ndk__read_object(env, argv[0], "group", &group);
  if (err < 0) return nullptr;

  java_object_t<"android/view/View"> child;
  err = bare_ndk__read_object(env, argv[1], "child", &child);
  if (err < 0) return nullptr;

  auto remove_view = group.get_class().get_method<void(java_object_t<"android/view/View">)>("removeView");

  remove_view(group, child);

  return nullptr;
}
