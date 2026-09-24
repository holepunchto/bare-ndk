#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <android/native_activity.h>

#include "bridging.h"

extern ANativeActivity *bare_native_activity;

static js_value_t *
bare_ndk_activity_init(js_env_t *env, js_callback_info_t *info) {
  auto activity = java_object_t<"android/app/Activity">(bare_jni__env(), bare_native_activity->clazz);

  return bare_ndk__tag(env, activity);
}

static js_value_t *
bare_ndk_activity_content_view(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/app/Activity"> activity;
  err = bare_ndk__read_object(env, argv[0], "activity", &activity);
  if (err < 0) return nullptr;

  java_object_t<"android/view/View"> view;
  err = bare_ndk__read_object(env, argv[1], "view", &view);
  if (err < 0) return nullptr;

  auto set_content_view = activity.get_class().get_method<void(java_object_t<"android/view/View">)>("setContentView");

  set_content_view(activity, view);

  return nullptr;
}

static js_value_t *
bare_ndk_activity_resources(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/app/Activity"> activity;
  err = bare_ndk__read_object(env, argv[0], "activity", &activity);
  if (err < 0) return nullptr;

  auto get_resources = activity.get_class().get_method<java_object_t<"android/content/res/Resources">()>("getResources");

  return bare_ndk__tag(env, get_resources(activity));
}
