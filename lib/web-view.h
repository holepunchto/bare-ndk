#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "activity.h"

struct bare_ndk_web_view_t {
  java_global_ref_t<java_object_t<"android/webkit/WebView">> handle;

  java_global_ref_t<java_class_t<"android/webkit/WebView">> init;

  js_env_t *env;
  js_ref_t *ctx;
};

static void
bare_ndk_web_view__on_release(js_env_t *env, bare_ndk_web_view_t *web_view) {
  int err;

  err = js_delete_reference(env, web_view->ctx);
  assert(err == 0);

  delete web_view;
}

static js_value_t *
bare_ndk_web_view_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  bare_ndk_activity_t *activity;
  err = js_get_value_external(env, js_external_t<bare_ndk_activity_t>(argv[0]), activity);
  assert(err == 0);

  auto web_view = new bare_ndk_web_view_t();

  web_view->env = env;

  web_view->init = java_class_t<"android/webkit/WebView">(activity->java);

  web_view->handle = web_view->init(java_object_t<"android/content/Context">(activity->java, activity->handle));

  err = js_create_reference(env, argv[1], 1, &web_view->ctx);
  assert(err == 0);

  js_external_t<bare_ndk_web_view_t> handle;
  err = js_create_external<bare_ndk_web_view__on_release>(env, web_view, handle);
  assert(err == 0);

  return static_cast<js_value_t *>(handle);
}

static js_value_t *
bare_ndk_web_view_load_url(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  bare_ndk_web_view_t *web_view;
  err = js_get_value_external(env, js_external_t<bare_ndk_web_view_t>(argv[0]), web_view);
  assert(err == 0);

  std::string url;
  err = js_get_value_string(env, js_string_t(argv[1]), url);
  assert(err == 0);

  auto load_url = web_view->init.get_method<void(std::string)>("loadUrl");

  load_url(web_view->handle, url);

  return nullptr;
}
