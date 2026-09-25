#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>
#include <jstl.h>

#include <string>

#include "activity.h"
#include "bridging.h"

enum {
  bare_ndk_edit_field_event_changed = 1 << 0,
  bare_ndk_edit_field_event_replacing = 1 << 1,
  bare_ndk_edit_field_event_selection_changed = 1 << 2,
  bare_ndk_edit_field_event_focus_changed = 1 << 3,
  bare_ndk_edit_field_event_action = 1 << 4,
};

static void
bare_ndk_edit_field__on_changed(java_env_t env, java_object_t<"to/holepunch/bare/ndk/EditField"> receiver) {
  bare_ndk__emit(receiver, "changed", 0, nullptr);
}

static void
bare_ndk_edit_field__on_selection(java_env_t env, java_object_t<"to/holepunch/bare/ndk/EditField"> receiver, int32_t start, int32_t end) {
  bare_ndk__emit(receiver, "selectionChanged", 2, (const double[]) {static_cast<double>(start), static_cast<double>(end)});
}

static void
bare_ndk_edit_field__on_focus(java_env_t env, java_object_t<"to/holepunch/bare/ndk/EditField"> receiver, bool focused) {
  bare_ndk__emit(receiver, "focusChanged", 1, (const double[]) {focused ? 1.0 : 0.0});
}

static void
bare_ndk_edit_field__on_action(java_env_t env, java_object_t<"to/holepunch/bare/ndk/EditField"> receiver) {
  bare_ndk__emit(receiver, "action", 0, nullptr);
}

static void
bare_ndk_edit_field__on_replacing(java_env_t env, java_object_t<"to/holepunch/bare/ndk/EditField"> receiver, std::string text, int32_t start, int32_t end) {
  bare_ndk__emit_replacement(receiver, "replacing", text, start, end);
}

static void
bare_ndk_edit_field_register(JNIEnv *jni) {
  java_class_t<"to/holepunch/bare/ndk/EditField">(jni, bare_ndk__class<"to/holepunch/bare/ndk/EditField">(jni))
    .register_natives(
      java_native_method_t<bare_ndk_edit_field__on_changed>("onChanged"),
      java_native_method_t<bare_ndk_edit_field__on_replacing>("onReplacing"),
      java_native_method_t<bare_ndk_edit_field__on_selection>("onSelection"),
      java_native_method_t<bare_ndk_edit_field__on_focus>("onFocus"),
      java_native_method_t<bare_ndk_edit_field__on_action>("onAction")
    );
}

static js_value_t *
bare_ndk_edit_field_init(js_env_t *env, js_callback_info_t *info) {
  JNIEnv *jni = bare_jni__env();

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto init = java_class_t<"to/holepunch/bare/ndk/EditField">(jni, bare_ndk__class<"to/holepunch/bare/ndk/EditField">(jni));

  return bare_ndk__tag(env, init(context));
}

static js_value_t *
bare_ndk_edit_field_event_mask(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"to/holepunch/bare/ndk/EditField"> field;
  err = bare_ndk__read_object(env, argv[0], "editField", &field);
  if (err < 0) return nullptr;

  int32_t mask;
  err = js_get_value(env, js_number_t(argv[1]), mask);
  assert(err == 0);

  field.get_class().get_method<void(int32_t)>("setEvents")(field, mask);

  return nullptr;
}

static js_value_t *
bare_ndk_edit_field_hint(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/widget/EditText"> field;
  err = bare_ndk__read_object(env, argv[0], "editField", &field);
  if (err < 0) return nullptr;

  std::string hint;
  err = js_get_value(env, js_string_t(argv[1]), hint);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  field.get_class().get_method<void(java_object_t<"java/lang/CharSequence">)>("setHint")(
    field, java_object_t<"java/lang/CharSequence">(jni, java_string_t(jni, hint))
  );

  return nullptr;
}

#define BARE_NDK_EDIT_FIELD_INT(name, getter, setter) \
  static js_value_t * \
  bare_ndk_edit_field_##name(js_env_t *env, js_callback_info_t *info) { \
    int err; \
\
    size_t argc = 2; \
    js_value_t *argv[2]; \
\
    err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr); \
    assert(err == 0); \
\
    assert(argc == 1 || argc == 2); \
\
    java_object_t<"android/widget/EditText"> field; \
    err = bare_ndk__read_object(env, argv[0], "editField", &field); \
    if (err < 0) return nullptr; \
\
    auto type = field.get_class(); \
\
    if (argc == 1) { \
      js_value_t *result; \
      err = js_create_int32(env, type.get_method<int32_t()>(getter)(field), &result); \
      assert(err == 0); \
\
      return result; \
    } \
\
    int32_t value; \
    err = js_get_value(env, js_number_t(argv[1]), value); \
    assert(err == 0); \
\
    type.get_method<void(int32_t)>(setter)(field, value); \
\
    return nullptr; \
  }

BARE_NDK_EDIT_FIELD_INT(input_type, "getInputType", "setInputType")
BARE_NDK_EDIT_FIELD_INT(ime_options, "getImeOptions", "setImeOptions")
#undef BARE_NDK_EDIT_FIELD_INT

static js_value_t *
bare_ndk_edit_field_selection(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 3;
  js_value_t *argv[3];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 1 || argc == 3);

  java_object_t<"android/widget/EditText"> field;
  err = bare_ndk__read_object(env, argv[0], "editField", &field);
  if (err < 0) return nullptr;

  auto type = field.get_class();

  if (argc == 1) {
    js_value_t *result;
    err = js_create_object(env, &result);
    assert(err == 0);

    js_value_t *value;

    err = js_create_int32(env, type.get_method<int32_t()>("getSelectionStart")(field), &value);
    assert(err == 0);

    err = js_set_named_property(env, result, "start", value);
    assert(err == 0);

    err = js_create_int32(env, type.get_method<int32_t()>("getSelectionEnd")(field), &value);
    assert(err == 0);

    err = js_set_named_property(env, result, "end", value);
    assert(err == 0);

    return result;
  }

  int32_t start;
  err = js_get_value(env, js_number_t(argv[1]), start);
  assert(err == 0);

  int32_t end;
  err = js_get_value(env, js_number_t(argv[2]), end);
  assert(err == 0);

  type.get_method<void(int32_t, int32_t)>("setSelection")(field, start, end);

  return nullptr;
}

// Focus and the soft keyboard are two things on Android: a view can hold focus
// with no keyboard showing, and only an `InputMethodManager` puts one there.
static js_value_t *
bare_ndk_edit_field_focus(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 2;
  js_value_t *argv[2];

  err = js_get_callback_info(env, info, &argc, argv, nullptr, nullptr);
  assert(err == 0);

  assert(argc == 2);

  java_object_t<"android/widget/EditText"> field;
  err = bare_ndk__read_object(env, argv[0], "editField", &field);
  if (err < 0) return nullptr;

  bool focused;
  err = js_get_value(env, js_boolean_t(argv[1]), focused);
  assert(err == 0);

  JNIEnv *jni = bare_jni__env();

  auto view = field.get_class();

  if (focused) {
    view.get_method<bool()>("requestFocus")(field);
  } else {
    view.get_method<void()>("clearFocus")(field);
  }

  auto context = java_object_t<"android/content/Context">(jni, bare_native_activity->clazz);

  auto service = context.get_class().get_method<java_object_t<"java/lang/Object">(std::string)>("getSystemService")(
    context, "input_method"
  );

  auto manager = java_object_t<"android/view/inputmethod/InputMethodManager">(jni, service);

  auto methods = java_class_t<"android/view/inputmethod/InputMethodManager">(jni, bare_ndk__class<"android/view/inputmethod/InputMethodManager">(jni));

  if (focused) {
    methods.get_method<bool(java_object_t<"android/view/View">, int32_t)>("showSoftInput")(
      manager, java_object_t<"android/view/View">(jni, field), 0
    );
  } else {
    auto token = view.get_method<java_object_t<"android/os/IBinder">()>("getWindowToken")(field);

    methods.get_method<bool(java_object_t<"android/os/IBinder">, int32_t)>("hideSoftInputFromWindow")(
      manager, token, 0
    );
  }

  return nullptr;
}
