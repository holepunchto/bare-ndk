#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include "activity.h"
#include "bridging.h"

enum {
  bare_ndk_toggle_event_checked = 1 << 0,
};

static void
bare_ndk_toggle__on_checked(java_env_t env, java_object_t<"to/holepunch/bare/ndk/Toggle"> receiver) {
  bare_ndk__emit(receiver, "checked", 0, nullptr);
}

static void
bare_ndk_toggle_register(JNIEnv *jni) {
  java_class_t<"to/holepunch/bare/ndk/Toggle">(jni, bare_ndk__class<"to/holepunch/bare/ndk/Toggle">(jni))
    .register_natives(
      java_native_method_t<bare_ndk_toggle__on_checked>("onChecked")
    );
}

static js_value_t *
bare_ndk_toggle_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"to/holepunch/bare/ndk/Toggle">(jni, bare_ndk__class<"to/holepunch/bare/ndk/Toggle">(jni));

  return bare_ndk__tag(env, init(context));
}

static js_value_t *
bare_ndk_toggle_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"to/holepunch/bare/ndk/Toggle"> toggle;
  err = bare_ndk__read_object(env, argv[0], "toggle", &toggle);
  if (err < 0) return nullptr;

  int32_t mask;
  err = js_get_value(env, js_number_t(argv[1]), mask);
  assert(err == 0);

  toggle.get_class().get_method<void(int32_t)>("setEvents")(toggle, mask);

  return nullptr;
}

static js_value_t *
bare_ndk_toggle_checked(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 2);

  java_object_t<"to/holepunch/bare/ndk/Toggle"> toggle;
  err = bare_ndk__read_object(env, argv[0], "toggle", &toggle);
  if (err < 0) return nullptr;

  auto type = toggle.get_class();

  js_value_t *result = nullptr;

  if (argc == 1) {
    err = js_get_boolean(env, type.get_method<bool()>("isChecked")(toggle), &result);
    assert(err == 0);
  } else {
    bool checked;
    err = js_get_value(env, js_boolean_t(argv[1]), checked);
    assert(err == 0);

    type.get_method<void(bool)>("setChecked")(toggle, checked);
  }

  return result;
}

// What a widget would draw itself at, which is the one thing the layout cannot
// work out for a control the toolkit draws.
static js_value_t *
bare_ndk_toggle_natural_size(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"to/holepunch/bare/ndk/Toggle"> toggle;
  err = bare_ndk__read_object(env, argv[0], "toggle", &toggle);
  if (err < 0) return nullptr;

  auto type = toggle.get_class();

  // An unspecified measure spec is a zero size and a zero mode, so the widget
  // answers with what it wants rather than with what it was offered.
  type.get_method<void(int32_t, int32_t)>("measure")(toggle, 0, 0);

  js_value_t *result;
  err = js_create_object(env, &result);
  assert(err == 0);

#define V(name, getter) \
  { \
    js_value_t *value; \
    err = js_create_int32(env, type.get_method<int32_t()>(getter)(toggle), &value); \
    assert(err == 0); \
    err = js_set_named_property(env, result, name, value); \
    assert(err == 0); \
  }
  V("width", "getMeasuredWidth")
  V("height", "getMeasuredHeight")
#undef V

  return result;
}
