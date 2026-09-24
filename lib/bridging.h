#pragma once

#include <assert.h>
#include <jnitl.h>
#include <js.h>
#include <stdint.h>
#include <string>
#include <utf.h>

#include "registry.h"

// What the addon keeps between calls. It belongs to one instantiation, because
// an addon can be loaded more than once in a process. Bindings reach it through
// their data pointer.
typedef struct bare_ndk_state_s bare_ndk_state_t;

struct bare_ndk_state_s {
  bare_jni_registry_t *registry;
  js_env_t *env;

  // Text is measured with a real `TextView`, rather than a `Paint` and a
  // `StaticLayout`, so it uses the same defaults as the view that draws it.
  jobject measured;
  jobject typeface;
  float text_size;

  bare_ndk_state_t *next;
};

// A callback from Java carries no hint of which instantiation it belongs to,
// because JNI binds native methods to a class. The live states are kept in a
// list, and the callback belongs to the one that has a wrapper for the
// receiver.
static bare_ndk_state_t *bare_ndk__states = nullptr;

static bare_ndk_state_t *
bare_ndk__state(jobject object) {
  for (bare_ndk_state_t *state = bare_ndk__states; state; state = state->next) {
    if (bare_jni_find(state->registry, bare_jni_env(), object)) return state;
  }

  return nullptr;
}

static void
bare_ndk__on_state_release(js_env_t *env, void *data, void *finalize_hint) {
  auto state = static_cast<bare_ndk_state_t *>(data);

  for (bare_ndk_state_t **link = &bare_ndk__states; *link; link = &(*link)->next) {
    if (*link != state) continue;

    *link = state->next;
    break;
  }

  JNIEnv *jni = bare_jni_env();

  if (state->measured) jni->DeleteGlobalRef(state->measured);
  if (state->typeface) jni->DeleteGlobalRef(state->typeface);

  bare_jni_registry_release(state->registry);

  delete state;
}

static bare_ndk_state_t *
bare_ndk_state_create(js_env_t *env, js_value_t *exports) {
  int err;

  auto state = new bare_ndk_state_t();

  state->registry = bare_jni_registry_create(env, exports);
  state->env = env;

  state->next = bare_ndk__states;
  bare_ndk__states = state;

  err = js_add_finalizer(env, exports, state, bare_ndk__on_state_release, nullptr, nullptr);
  assert(err == 0);

  return state;
}

// Defined by the runtime. See `lib/runtime.cc`.
extern "C" void
bare_native_wake(void);

// `FindClass` cannot see the app's own classes from native code, so every class
// comes from the class loader of the activity thread. Each instantiation looks
// a class up once.
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
bare_ndk__read_object(js_env_t *env, bare_ndk_state_t *state, js_value_t *value, const char *name, java_object_t<N> *result) {
  int err;

  JNIEnv *jni = bare_jni_env();

  jobject object;
  err = bare_jni_read_type(env, state->registry, value, name, bare_ndk__class<N>(jni), &object);
  if (err < 0) return err;

  *result = java_object_t<N>(jni, object);

  return 0;
}

template <java_class_name_t N>
static js_value_t *
bare_ndk__tag(js_env_t *env, bare_ndk_state_t *state, const java_object_t<N> &object) {
  int err;

  js_value_t *result;
  err = js_create_uint32(env, bare_jni_tag(state->registry, object), &result);
  assert(err == 0);

  return result;
}

// Emit an edit as it happens, as the range it replaces and the new text.
static void
bare_ndk__emit_replacement(jobject object, const char *event, const std::string &text, int32_t start, int32_t end) {
  int err;

  bare_ndk_state_t *state = bare_ndk__state(object);

  if (state == nullptr) return;

  js_env_t *env = state->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *wrapper = bare_jni_lookup(env, state->registry, object);

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

  bare_ndk_state_t *state = bare_ndk__state(object);

  if (state == nullptr) return;

  js_env_t *env = state->env;

  js_handle_scope_t *scope;
  err = js_open_handle_scope(env, &scope);
  assert(err == 0);

  js_value_t *wrapper = bare_jni_lookup(env, state->registry, object);

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
