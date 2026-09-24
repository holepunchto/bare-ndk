#include <assert.h>
#include <bare.h>
#include <js.h>
#include <utf.h>

#include "lib/activity.h"
#include "lib/bridging.h"
#include "lib/drawable.h"
#include "lib/frame-group.h"
#include "lib/resources.h"
#include "lib/scroll-view.h"
#include "lib/text-view.h"
#include "lib/text.h"
#include "lib/typeface.h"
#include "lib/view-group.h"
#include "lib/view.h"
#include "lib/web-settings.h"
#include "lib/window-insets.h"
#include "lib/web-view.h"

static js_value_t *
bare_ndk_exports(js_env_t *env, js_value_t *exports) {
  int err;

  // JNI has no ambient environment, so the registry is handed the activity's.
  bare_jni_attach(bare_native_activity->env);

  bare_ndk__js = env;

  bare_ndk_frame_group_register(bare_native_activity->env);
  bare_ndk_scroll_view_register(bare_native_activity->env);

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, nullptr, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("claim", bare_jni_claim)
  V("wrapper", bare_jni_wrapper)
  V("registrySize", bare_jni_registry_size)
  V("handle", bare_jni_handle)
  V("adopt", bare_jni_adopt)

  V("activityInit", bare_ndk_activity_init)
  V("activityContentView", bare_ndk_activity_content_view)
  V("activityResources", bare_ndk_activity_resources)

  V("resourcesDisplayMetrics", bare_ndk_resources_display_metrics)

  V("viewBackgroundColor", bare_ndk_view_background_color)
  V("viewWidth", bare_ndk_view_width)
  V("viewHeight", bare_ndk_view_height)
  V("viewRootWindowInsets", bare_ndk_view_root_window_insets)
  V("viewAlpha", bare_ndk_view_alpha)
  V("viewClipToOutline", bare_ndk_view_clip_to_outline)
  V("viewBackground", bare_ndk_view_background)

  V("windowInsetsInsets", bare_ndk_window_insets_insets)

  V("viewGroupAddView", bare_ndk_view_group_add_view)
  V("viewGroupRemoveView", bare_ndk_view_group_remove_view)

  V("scrollViewInit", bare_ndk_scroll_view_init)
  V("scrollViewEventMask", bare_ndk_scroll_view_event_mask)
  V("viewScrollPosition", bare_ndk_view_scroll_position)
  V("horizontalScrollViewInit", bare_ndk_horizontal_scroll_view_init)

  V("frameGroupInit", bare_ndk_frame_group_init)
  V("frameGroupSetFrame", bare_ndk_frame_group_set_frame)
  V("frameGroupEventMask", bare_ndk_frame_group_event_mask)

  V("textMeasure", bare_ndk_text_measure)

  V("textViewInit", bare_ndk_text_view_init)
  V("textViewText", bare_ndk_text_view_text)
  V("textViewTextSize", bare_ndk_text_view_text_size)
  V("textViewTextColor", bare_ndk_text_view_text_color)
  V("textViewTypeface", bare_ndk_text_view_typeface)
  V("textViewGravity", bare_ndk_text_view_gravity)
  V("textViewJustificationMode", bare_ndk_text_view_justification_mode)

  V("typefaceCreate", bare_ndk_typeface_create)

  V("gradientDrawableInit", bare_ndk_gradient_drawable_init)
  V("gradientDrawableColor", bare_ndk_gradient_drawable_color)
  V("gradientDrawableCornerRadius", bare_ndk_gradient_drawable_corner_radius)
  V("gradientDrawableStroke", bare_ndk_gradient_drawable_stroke)

  V("webViewInit", bare_ndk_web_view_init)
  V("webViewDebuggingEnabled", bare_ndk_web_view_debugging_enabled)
  V("webViewSettings", bare_ndk_web_view_settings)
  V("webViewLoadURL", bare_ndk_web_view_load_url)
  V("webViewLoadData", bare_ndk_web_view_load_data)
  V("webViewLoadDataWithBaseURL", bare_ndk_web_view_load_data_with_base_url)

  V("webSettingsJavaScriptEnabled", bare_ndk_web_settings_java_script_enabled)
  V("webSettingsDomStorageEnabled", bare_ndk_web_settings_dom_storage_enabled)
  V("webSettingsUserAgentString", bare_ndk_web_settings_user_agent_string)
#undef V

#define V(name, n) \
  { \
    js_value_t *val; \
    err = js_create_int32(env, n, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("FRAME_GROUP_EVENT_RESIZE", bare_ndk_frame_group_event_resize)
  V("SCROLL_VIEW_EVENT_SCROLL", bare_ndk_scroll_view_event_scroll)

  V("FRAME_GROUP_EVENT_DOWN", bare_ndk_frame_group_event_down)
  V("FRAME_GROUP_EVENT_MOVE", bare_ndk_frame_group_event_move)
  V("FRAME_GROUP_EVENT_UP", bare_ndk_frame_group_event_up)
  V("FRAME_GROUP_EVENT_CANCEL", bare_ndk_frame_group_event_cancel)

  V("WINDOW_INSETS_TYPE_SYSTEM_BARS", bare_ndk__window_insets_type("systemBars"))
  V("WINDOW_INSETS_TYPE_DISPLAY_CUTOUT", bare_ndk__window_insets_type("displayCutout"))
  V("WINDOW_INSETS_TYPE_IME", bare_ndk__window_insets_type("ime"))
#undef V

  return exports;
}

BARE_MODULE(bare_ndk, bare_ndk_exports)
