#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <string>

#include "bridging.h"

static js_value_t *
bare_ndk_web_settings_java_script_enabled(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"android/webkit/WebSettings"> settings;
  err = bare_ndk__read_object(env, argv[0], "settings", &settings);
  if (err < 0) return nullptr;

  js_value_t *result = nullptr;

  if (argc == 1) {
    auto get = settings.get_class().get_method<bool()>("getJavaScriptEnabled");

    err = js_get_boolean(env, get(settings), &result);
    assert(err == 0);
  } else {
    bool enabled;
    err = js_get_value(env, js_boolean_t(argv[1]), enabled);
    assert(err == 0);

    auto set = settings.get_class().get_method<void(bool)>("setJavaScriptEnabled");

    set(settings, enabled);
  }

  return result;
}

static js_value_t *
bare_ndk_web_settings_dom_storage_enabled(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"android/webkit/WebSettings"> settings;
  err = bare_ndk__read_object(env, argv[0], "settings", &settings);
  if (err < 0) return nullptr;

  js_value_t *result = nullptr;

  if (argc == 1) {
    auto get = settings.get_class().get_method<bool()>("getDomStorageEnabled");

    err = js_get_boolean(env, get(settings), &result);
    assert(err == 0);
  } else {
    bool enabled;
    err = js_get_value(env, js_boolean_t(argv[1]), enabled);
    assert(err == 0);

    auto set = settings.get_class().get_method<void(bool)>("setDomStorageEnabled");

    set(settings, enabled);
  }

  return result;
}

static js_value_t *
bare_ndk_web_settings_user_agent_string(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"android/webkit/WebSettings"> settings;
  err = bare_ndk__read_object(env, argv[0], "settings", &settings);
  if (err < 0) return nullptr;

  js_value_t *result = nullptr;

  if (argc == 1) {
    auto get = settings.get_class().get_method<std::string()>("getUserAgentString");

    js_string_t string;
    err = js_create_string(env, get(settings), string);
    assert(err == 0);

    result = static_cast<js_value_t *>(string);
  } else {
    std::string agent;
    err = js_get_value(env, js_string_t(argv[1]), agent);
    assert(err == 0);

    auto set = settings.get_class().get_method<void(std::string)>("setUserAgentString");

    set(settings, agent);
  }

  return result;
}
