#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

static js_value_t *
bare_ndk_resources_display_metrics(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/content/res/Resources"> resources;
  err = bare_ndk__read_object(env, state, argv[0], "resources", &resources);
  if (err < 0) return nullptr;

  auto get_metrics = resources.get_class().get_method<java_object_t<"android/util/DisplayMetrics">()>("getDisplayMetrics");

  auto metrics = get_metrics(resources);

  auto type = metrics.get_class();

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

  for (auto name : {"density", "scaledDensity", "xdpi", "ydpi"}) {
    js_value_t *value;
    err = js_create_double(env, metrics.get(type.get_field<float>(name)), &value);
    assert(err == 0);

    err = js_set_named_property(env, result, name, value);
    assert(err == 0);
  }

  for (auto name : {"densityDpi", "widthPixels", "heightPixels"}) {
    js_value_t *value;
    err = js_create_int32(env, metrics.get(type.get_field<int32_t>(name)), &value);
    assert(err == 0);

    err = js_set_named_property(env, result, name, value);
    assert(err == 0);
  }

  return result;
}

static js_value_t *
bare_ndk_resources_configuration(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/content/res/Resources"> resources;
  err = bare_ndk__read_object(env, state, argv[0], "resources", &resources);
  if (err < 0) return nullptr;

  auto get_configuration = resources.get_class().get_method<java_object_t<"android/content/res/Configuration">()>("getConfiguration");

  auto configuration = get_configuration(resources);

  auto type = configuration.get_class();

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

  for (auto name : {"uiMode", "orientation", "densityDpi", "screenWidthDp", "screenHeightDp", "smallestScreenWidthDp"}) {
    js_value_t *value;
    err = js_create_int32(env, configuration.get(type.get_field<int32_t>(name)), &value);
    assert(err == 0);

    err = js_set_named_property(env, result, name, value);
    assert(err == 0);
  }

  js_value_t *scale;
  err = js_create_double(env, configuration.get(type.get_field<float>("fontScale")), &scale);
  assert(err == 0);

  err = js_set_named_property(env, result, "fontScale", scale);
  assert(err == 0);

  return result;
}

static int32_t
bare_ndk__configuration_constant(const char *name) {
  JNIEnv *jni = bare_jni_env();

  auto type = java_class_t<"android/content/res/Configuration">(jni, bare_ndk__class<"android/content/res/Configuration">(jni));

  return type.get_static_field<int32_t>(name).get();
}
