#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "bridging.h"

// A `WindowInsets.Type` is a static method, so the masks are read once at load.
static int32_t
bare_ndk__window_insets_type(const char *name) {
  JNIEnv *jni = bare_jni__env();

  auto type = java_class_t<"android/view/WindowInsets$Type">(jni, bare_ndk__class<"android/view/WindowInsets$Type">(jni));

  return type.get_static_method<int32_t()>(name)();
}

// Plain data rather than a tag, which is the line every platform draws for a
// value type.
static js_value_t *
bare_ndk_window_insets_insets(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/view/WindowInsets"> insets;
  err = bare_ndk__read_object(env, argv[0], "insets", &insets);
  if (err < 0) return nullptr;

  int32_t mask;
  err = js_get_value(env, js_number_t(argv[1]), mask);
  assert(err == 0);

  auto get_insets = insets.get_class().get_method<java_object_t<"android/graphics/Insets">(int32_t)>("getInsets");

  auto edges = get_insets(insets, mask);

  auto type = edges.get_class();

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

  for (auto name : {"top", "right", "bottom", "left"}) {
    js_value_t *value;
    err = js_create_int32(env, edges.get(type.get_field<int32_t>(name)), &value);
    assert(err == 0);

    err = js_set_named_property(env, result, name, value);
    assert(err == 0);
  }

  return result;
}
