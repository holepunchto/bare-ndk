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
static inline java_object_t<"android/content/ClipboardManager">
bare_ndk__clipboard_manager(JNIEnv *jni) {
  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto service = context.get_class().get_method<java_object_t<"java/lang/Object">(std::string)>("getSystemService")(
    context, "clipboard"
  );

  return java_object_t<"android/content/ClipboardManager">(jni, service);
}

static js_value_t *
bare_ndk_clipboard_manager_set_primary_clip(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1);

  java_object_t<"android/content/ClipData"> clip;
  err = bare_ndk__read_object(env, state, argv[0], "clip", &clip);
  if (err < 0) return nullptr;

  JNIEnv *jni = bare_jni_env();

  auto manager = bare_ndk__clipboard_manager(jni);

  manager.get_class().get_method<void(java_object_t<"android/content/ClipData">)>("setPrimaryClip")(manager, clip);

  return nullptr;
}

static js_value_t *
bare_ndk_clipboard_manager_get_primary_clip(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  JNIEnv *jni = bare_jni_env();

  auto manager = bare_ndk__clipboard_manager(jni);

  auto clip = manager.get_class().get_method<java_object_t<"android/content/ClipData">()>("getPrimaryClip")(manager);

  if (clip == nullptr) {
    js_value_t *result;
    err = js_get_null(env, &result);
    assert(err == 0);

    return result;
  }

  return bare_ndk__tag(env, state, clip);
}

static js_value_t *
bare_ndk_clipboard_manager_has_primary_clip(js_env_t *env, js_callback_info_t *info) {
  int err;

  JNIEnv *jni = bare_jni_env();

  auto manager = bare_ndk__clipboard_manager(jni);

  auto has = manager.get_class().get_method<bool()>("hasPrimaryClip")(manager);

  js_value_t *result;
  err = js_get_boolean(env, has, &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_ndk_clipboard_manager_clear_primary_clip(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni_env();

  auto manager = bare_ndk__clipboard_manager(jni);

  manager.get_class().get_method<void()>("clearPrimaryClip")(manager);

  return nullptr;
}
