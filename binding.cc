#include <assert.h>
#include <bare.h>
#include <js.h>
#include <utf.h>

#include "lib/activity.h"
#include "lib/web-view.h"

static js_value_t *
bare_ndk_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, nullptr, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("activityInit", bare_ndk_activity_init)
  V("activityContentView", bare_ndk_activity_content_view)

  V("webViewInit", bare_ndk_web_view_init)
  V("webViewLoadURL", bare_ndk_web_view_load_url)
#undef V

#define V(name, n) \
  { \
    js_value_t *val; \
    err = js_create_int32(env, n, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }
#undef V

  return exports;
}

BARE_MODULE(bare_ndk, bare_ndk_exports)
