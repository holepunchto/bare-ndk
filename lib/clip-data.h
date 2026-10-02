#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <string>

#include "bridging.h"

static js_value_t *
bare_ndk_clip_data_new_plain_text(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  std::string label;
  err = js_get_value(env, js_string_t(argv[0]), label);
  assert(err == 0);

  std::string text;
  err = js_get_value(env, js_string_t(argv[1]), text);
  assert(err == 0);

  JNIEnv *jni = bare_jni_env();

  auto type = java_class_t<"android/content/ClipData">(jni, bare_ndk__class<"android/content/ClipData">(jni));

  auto clip = type.get_static_method<java_object_t<"android/content/ClipData">(java_object_t<"java/lang/CharSequence">, java_object_t<"java/lang/CharSequence">)>("newPlainText")(
    java_object_t<"java/lang/CharSequence">(jni, java_string_t(jni, label)),
    java_object_t<"java/lang/CharSequence">(jni, java_string_t(jni, text))
  );

  return bare_ndk__tag(env, state, clip);
}

static js_value_t *
bare_ndk_clip_data_item_count(js_env_t *env, js_callback_info_t *info) {
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

  js_value_t *result;
  err = js_create_int32(env, clip.get_class().get_method<int32_t()>("getItemCount")(clip), &result);
  assert(err == 0);

  return result;
}

static js_value_t *
bare_ndk_clip_data_get_item_at(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/content/ClipData"> clip;
  err = bare_ndk__read_object(env, state, argv[0], "clip", &clip);
  if (err < 0) return nullptr;

  int32_t index;
  err = js_get_value(env, js_number_t(argv[1]), index);
  assert(err == 0);

  auto item = clip.get_class().get_method<java_object_t<"android/content/ClipData$Item">(int32_t)>("getItemAt")(clip, index);

  return bare_ndk__tag(env, state, item);
}

// An item can hold a URI or an intent instead of text. Coercing is how Android
// turns either into text.
static js_value_t *
bare_ndk_clip_data_item_coerce_to_text(js_env_t *env, js_callback_info_t *info) {
  int err;

  bare_ndk_state_t *state;
  err = js_get_callback_info(env, info, NULL, NULL, NULL, (void **) &state);
  assert(err == 0);

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/content/ClipData$Item"> item;
  err = bare_ndk__read_object(env, state, argv[0], "item", &item);
  if (err < 0) return nullptr;

  java_object_t<"android/content/Context"> context;
  err = bare_ndk__read_object(env, state, argv[1], "context", &context);
  if (err < 0) return nullptr;

  auto text = item.get_class().get_method<java_object_t<"java/lang/CharSequence">(java_object_t<"android/content/Context">)>("coerceToText")(item, context);

  if (text == nullptr) {
    js_value_t *result;
    err = js_get_null(env, &result);
    assert(err == 0);

    return result;
  }

  auto string = text.get_class().get_method<std::string()>("toString")(text);

  js_string_t result;
  err = js_create_string(env, string, result);
  assert(err == 0);

  return static_cast<js_value_t *>(result);
}
