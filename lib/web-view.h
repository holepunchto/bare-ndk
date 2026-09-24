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
bare_ndk_web_view_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"android/webkit/WebView">(jni);

  auto web_view = init(context);

  return bare_ndk__tag(env, web_view);
}

static js_value_t *
bare_ndk_web_view_debugging_enabled(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  bool enabled;
  err = js_get_value(env, js_boolean_t(argv[0]), enabled);
  assert(err == 0);

  auto init = java_class_t<"android/webkit/WebView">(bare_jni__env());

  auto set_debugging_enabled = init.get_static_method<void(bool)>("setWebContentsDebuggingEnabled");

  set_debugging_enabled(enabled);

  return nullptr;
}

static js_value_t *
bare_ndk_web_view_settings(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/webkit/WebView"> web_view;
  err = bare_ndk__read_object(env, argv[0], "webView", &web_view);
  if (err < 0) return nullptr;

  auto get_settings = web_view.get_class().get_method<java_object_t<"android/webkit/WebSettings">()>("getSettings");

  return bare_ndk__tag(env, get_settings(web_view));
}

static js_value_t *
bare_ndk_web_view_load_url(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/webkit/WebView"> web_view;
  err = bare_ndk__read_object(env, argv[0], "webView", &web_view);
  if (err < 0) return nullptr;

  std::string url;
  err = js_get_value(env, js_string_t(argv[1]), url);
  assert(err == 0);

  auto load_url = web_view.get_class().get_method<void(std::string)>("loadUrl");

  load_url(web_view, url);

  return nullptr;
}

static js_value_t *
bare_ndk_web_view_load_data(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 4;
  js_value_t *argv[4];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 4);

  java_object_t<"android/webkit/WebView"> web_view;
  err = bare_ndk__read_object(env, argv[0], "webView", &web_view);
  if (err < 0) return nullptr;

  std::string data;
  err = js_get_value(env, js_string_t(argv[1]), data);
  assert(err == 0);

  std::string mime_type;
  err = js_get_value(env, js_string_t(argv[2]), mime_type);
  assert(err == 0);

  std::string encoding;
  err = js_get_value(env, js_string_t(argv[3]), encoding);
  assert(err == 0);

  auto load_data = web_view.get_class().get_method<void(std::string, std::string, std::string)>("loadData");

  load_data(web_view, data, mime_type, encoding);

  return nullptr;
}

static js_value_t *
bare_ndk_web_view_load_data_with_base_url(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 6;
  js_value_t *argv[6];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 6);

  java_object_t<"android/webkit/WebView"> web_view;
  err = bare_ndk__read_object(env, argv[0], "webView", &web_view);
  if (err < 0) return nullptr;

  std::string base_url;
  err = js_get_value(env, js_string_t(argv[1]), base_url);
  assert(err == 0);

  std::string data;
  err = js_get_value(env, js_string_t(argv[2]), data);
  assert(err == 0);

  std::string mime_type;
  err = js_get_value(env, js_string_t(argv[3]), mime_type);
  assert(err == 0);

  std::string encoding;
  err = js_get_value(env, js_string_t(argv[4]), encoding);
  assert(err == 0);

  std::string history_url;
  err = js_get_value(env, js_string_t(argv[5]), history_url);
  assert(err == 0);

  auto load_data = web_view.get_class().get_method<void(std::string, std::string, std::string, std::string, std::string)>("loadDataWithBaseURL");

  load_data(web_view, base_url, data, mime_type, encoding, history_url);

  return nullptr;
}
