#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <string>

#include "activity.h"
#include "bridging.h"

static void
bare_ndk_dialog__on_response(java_env_t env, java_object_t<"to/holepunch/bare/ndk/Dialog"> receiver, int32_t which) {
  bare_ndk__emit(receiver, "response", 1, (const double[]) {double(which)});
}

static void
bare_ndk_dialog_register(JNIEnv *jni) {
  java_class_t<"to/holepunch/bare/ndk/Dialog">(jni, bare_ndk__class<"to/holepunch/bare/ndk/Dialog">(jni))
    .register_natives(java_native_method_t<bare_ndk_dialog__on_response>("onResponse"));
}

// A button that is `null` is not shown.
static java_object_t<"java/lang/String">
bare_ndk_dialog__label(js_env_t *env, JNIEnv *jni, js_value_t *value) {
  int err;

  js_value_type_t type;
  err = js_typeof(env, value, &type);
  assert(err == 0);

  if (type != js_string) return java_object_t<"java/lang/String">();

  std::string label;
  err = js_get_value(env, js_string_t(value), label);
  assert(err == 0);

  return java_string_t(jni, label);
}

static int32_t
bare_ndk__dialog_interface_constant(const char *name) {
  JNIEnv *jni = bare_jni_env();

  auto type = java_class_t<"android/content/DialogInterface">(jni, bare_ndk__class<"android/content/DialogInterface">(jni));

  return type.get_static_field<int32_t>(name).get();
}

static js_value_t *
bare_ndk_dialog_init(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 5;
  js_value_t *argv[5];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 5);

  std::string title;
  err = js_get_value(env, js_string_t(argv[0]), title);
  assert(err == 0);

  JNIEnv *jni = bare_jni_env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"to/holepunch/bare/ndk/Dialog">(jni, bare_ndk__class<"to/holepunch/bare/ndk/Dialog">(jni));

  return bare_ndk__tag(
    env,
    state,
    init(
      context,
      java_string_t(jni, title),
      bare_ndk_dialog__label(env, jni, argv[1]),
      bare_ndk_dialog__label(env, jni, argv[2]),
      bare_ndk_dialog__label(env, jni, argv[3]),
      bare_ndk_dialog__label(env, jni, argv[4])
    )
  );
}

static js_value_t *
bare_ndk_dialog_show(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"to/holepunch/bare/ndk/Dialog"> dialog;
  err = bare_ndk__read_object(env, state, argv[0], "dialog", &dialog);
  if (err < 0) return nullptr;

  dialog.get_class().get_method<void()>("show")(dialog);

  return nullptr;
}
