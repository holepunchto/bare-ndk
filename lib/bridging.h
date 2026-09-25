#pragma once

#include <assert.h>
#include <jnitl.h>
#include <js.h>
#include <stdint.h>
#include <string>
#include <utf.h>

#include "registry.h"

// A Java callback arrives with an environment for the VM and none for the
// runtime, so the one the module was given is kept.
static js_env_t *bare_ndk__js = nullptr;

// Defined by the runtime. See `lib/runtime.cc`.
extern "C" void
bare_native_wake(void);

// `FindClass` cannot see an application's own classes from native code, so
// every class comes from the loader of the thread the activity runs on. Each
// instantiation has its own static, so a class is looked up once.
template <java_class_name_t N>
static jclass
bare_ndk__class(JNIEnv *env) {
  static jclass resolved = nullptr;

  if (resolved == nullptr) {
    auto loader = java_thread_t::current_thread(env).get_context_class_loader();

    resolved = static_cast<jclass>(env->NewGlobalRef(loader.load_class<N>()));
  }

  return resolved;
}

template <java_class_name_t N>
static int
bare_ndk__read_object(js_env_t *env, js_value_t *value, const char *name, java_object_t<N> *result) {
  int err;

  JNIEnv *jni = bare_jni__env();

  jobject object;
  err = bare_jni__read_type(env, value, name, bare_ndk__class<N>(jni), &object);
  if (err < 0) return err;

  *result = java_object_t<N>(jni, object);

  return 0;
}

template <java_class_name_t N>
static js_value_t *
bare_ndk__tag(js_env_t *env, const java_object_t<N> &object) {
  int err;

  js_value_t *result;
  err = js_create_uint32(env, bare_jni__tag(object), &result);
  assert(err == 0);

  return result;
}

// A range and the string about to replace it, which is what a text watcher
// reports about an edit as it happens.
static void
bare_ndk__emit_replacement(jobject object, const char *event, const std::string &text, int32_t start, int32_t end) {
  int err;

  js_env_t *env = bare_ndk__js;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *wrapper = bare_jni__lookup(env, object);

  if (wrapper) {
    js_value_t *emit;
    err = js_get_named_property(env, wrapper, "emit", &emit);
    assert(err == 0);

    js_value_t *argv[4];

    err = js_create_string_utf8(env, reinterpret_cast<const utf8_t *>(event), (size_t) -1, &argv[0]);
    assert(err == 0);

    err = js_create_string_utf8(env, reinterpret_cast<const utf8_t *>(text.c_str()), text.size(), &argv[1]);
    assert(err == 0);

    err = js_create_int32(env, start, &argv[2]);
    assert(err == 0);

    err = js_create_int32(env, end, &argv[3]);
    assert(err == 0);

    err = js_call_function(env, wrapper, emit, 4, argv, nullptr);
    assert(err == 0 || err == js_pending_exception);
  }

  err = js_close_handle_scope(env, scope);
  assert(err == 0);

  bare_native_wake();
}

static void
bare_ndk__emit(jobject object, const char *event, size_t argc, const double args[]) {
  int err;

  js_env_t *env = bare_ndk__js;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *wrapper = bare_jni__lookup(env, object);

  if (wrapper) {
    js_value_t *emit;
    err = js_get_named_property(env, wrapper, "emit", &emit);
    assert(err == 0);

    js_value_t *argv[8];

    assert(argc + 1 <= 8);

    err = js_create_string_utf8(env, reinterpret_cast<const utf8_t *>(event), (size_t) -1, &argv[0]);
    assert(err == 0);

    for (size_t i = 0; i < argc; i++) {
      err = js_create_double(env, args[i], &argv[i + 1]);
      assert(err == 0);
    }

    err = js_call_function(env, wrapper, emit, argc + 1, argv, nullptr);
    assert(err == 0 || err == js_pending_exception);
  }

  err = js_close_handle_scope(env, scope);
  assert(err == 0);

  bare_native_wake();
}
