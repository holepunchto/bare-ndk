#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

// Plain data, like `Insets`: numbers Android fills in rather than an object.
static js_value_t *
bare_ndk_resources_display_metrics(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/content/res/Resources"> resources;
  err = bare_ndk__read_object(env, argv[0], "resources", &resources);
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
