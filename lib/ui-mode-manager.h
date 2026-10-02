#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <string>

#include "activity.h"
#include "bridging.h"

// Looked up each time instead of kept, because a system service belongs to the
// context.
static js_value_t *
bare_ndk_ui_mode_manager_application_night_mode(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  int32_t mode;
  err = js_get_value(env, js_number_t(argv[0]), mode);
  assert(err == 0);

  JNIEnv *jni = bare_jni_env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto service = context.get_class().get_method<java_object_t<"java/lang/Object">(std::string)>("getSystemService")(
    context, "uimode"
  );

  auto manager = java_object_t<"android/app/UiModeManager">(jni, service);

  auto methods = java_class_t<"android/app/UiModeManager">(jni, bare_ndk__class<"android/app/UiModeManager">(jni));

  methods.get_method<void(int32_t)>("setApplicationNightMode")(manager, mode);

  return nullptr;
}

static int32_t
bare_ndk__ui_mode_manager_constant(const char *name) {
  JNIEnv *jni = bare_jni_env();

  auto type = java_class_t<"android/app/UiModeManager">(jni, bare_ndk__class<"android/app/UiModeManager">(jni));

  return type.get_static_field<int32_t>(name).get();
}
