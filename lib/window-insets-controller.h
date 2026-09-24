#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

static js_value_t *
bare_ndk_window_insets_controller__toggle(js_env_t *env, js_callback_info_t *info, const char *method) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/WindowInsetsController"> controller;
  err = bare_ndk__read_object(env, state, argv[0], "controller", &controller);
  if (err < 0) return nullptr;

  int32_t types;
  err = js_get_value(env, js_number_t(argv[1]), types);
  assert(err == 0);

  controller.get_class().get_method<void(int32_t)>(method)(controller, types);

  return nullptr;
}

static js_value_t *
bare_ndk_window_insets_controller_show(js_env_t *env, js_callback_info_t *info) {
  return bare_ndk_window_insets_controller__toggle(env, info, "show");
}

static js_value_t *
bare_ndk_window_insets_controller_hide(js_env_t *env, js_callback_info_t *info) {
  return bare_ndk_window_insets_controller__toggle(env, info, "hide");
}
