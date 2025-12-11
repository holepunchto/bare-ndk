#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <android/native_activity.h>

#include "view.h"

extern ANativeActivity *bare_native_activity;

struct bare_ndk_activity_t {
  java_global_ref_t<java_object_t<"android/app/Activity">> handle;

  java_global_ref_t<java_class_t<"android/app/Activity">> init;

  java_env_t java;
};

static js_value_t *
bare_ndk_activity_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  auto activity = new bare_ndk_activity_t();

  activity->java = bare_native_activity->env;

  activity->init = java_class_t<"android/app/Activity">(activity->java);

  activity->handle = java_object_t<"android/app/Activity">(activity->java, bare_native_activity->clazz);

  js_external_t<bare_ndk_activity_t> handle;
  err = js_create_external(env, activity, handle);
  assert(err == 0);

  return static_cast<js_value_t *>(handle);
}

static js_value_t *
bare_ndk_activity_content_view(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  bare_ndk_activity_t *activity;
  err = js_get_value(env, js_external_t<bare_ndk_activity_t>(argv[0]), activity);
  assert(err == 0);

  bare_ndk_view_t *view;
  err = js_get_value(env, js_external_t<bare_ndk_view_t>(argv[1]), view);
  assert(err == 0);

  auto set_content_view = activity->init.get_method<void(java_object_t<"android/view/View">)>("setContentView");

  set_content_view(activity->handle, view->handle);

  return nullptr;
}
