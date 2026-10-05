#include <assert.h>
#include <bare.h>
#include <js.h>
#include <utf.h>

#include "lib/activity.h"
#include "lib/bitmap.h"
#include "lib/bridging.h"
#include "lib/drawable.h"
#include "lib/edit-field.h"
#include "lib/progress-bar.h"
#include "lib/choreographer.h"
#include "lib/frame-callback.h"
#include "lib/toggle.h"
#include "lib/frame-group.h"
#include "lib/image-view.h"
#include "lib/resources.h"
#include "lib/scroll-view.h"
#include "lib/span.h"
#include "lib/spannable-string-builder.h"
#include "lib/text-view.h"
#include "lib/text.h"
#include "lib/typeface.h"
#include "lib/view-group.h"
#include "lib/clip-data.h"
#include "lib/clipboard-manager.h"
#include "lib/dialog.h"
#include "lib/ui-mode-manager.h"
#include "lib/view.h"
#include "lib/web-settings.h"
#include "lib/window-insets.h"
#include "lib/window-insets-controller.h"
#include "lib/web-view.h"

static js_value_t *
bare_ndk_exports(js_env_t *env, js_value_t *exports) {
  int err;

  // JNI has no ambient environment, so the registry is given the activity's.
  bare_jni_attach(bare_native_activity->env);

  bare_ndk_state_t *state = bare_ndk_state_create(env, exports);

  bare_ndk_frame_group_register(bare_native_activity->env);
  bare_ndk_scroll_view_register(bare_native_activity->env);
  bare_ndk_edit_field_register(bare_native_activity->env);
  bare_ndk_frame_callback_register(bare_native_activity->env);
  bare_ndk_toggle_register(bare_native_activity->env);
  bare_ndk_dialog_register(bare_native_activity->env);

#define V(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, state, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  // The registry's own functions take the registry, not the state around it.
#define R(name, fn) \
  { \
    js_value_t *val; \
    err = js_create_function(env, name, -1, fn, state->registry, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  R("claim", bare_jni_claim)
  R("wrapper", bare_jni_wrapper)
  R("registrySize", bare_jni_registry_size)
  R("handle", bare_jni_handle)
  R("adopt", bare_jni_adopt)

  V("activityInit", bare_ndk_activity_init)
  V("activityContentView", bare_ndk_activity_content_view)
  V("activityResources", bare_ndk_activity_resources)

  V("resourcesDisplayMetrics", bare_ndk_resources_display_metrics)
  V("resourcesConfiguration", bare_ndk_resources_configuration)

  V("uiModeManagerApplicationNightMode", bare_ndk_ui_mode_manager_application_night_mode)

  V("dialogInit", bare_ndk_dialog_init)
  V("dialogShow", bare_ndk_dialog_show)

  V("clipDataNewPlainText", bare_ndk_clip_data_new_plain_text)
  V("clipDataItemCount", bare_ndk_clip_data_item_count)
  V("clipDataGetItemAt", bare_ndk_clip_data_get_item_at)
  V("clipDataItemCoerceToText", bare_ndk_clip_data_item_coerce_to_text)

  V("clipboardManagerSetPrimaryClip", bare_ndk_clipboard_manager_set_primary_clip)
  V("clipboardManagerGetPrimaryClip", bare_ndk_clipboard_manager_get_primary_clip)
  V("clipboardManagerHasPrimaryClip", bare_ndk_clipboard_manager_has_primary_clip)
  V("clipboardManagerClearPrimaryClip", bare_ndk_clipboard_manager_clear_primary_clip)

  V("viewBackgroundColor", bare_ndk_view_background_color)
  V("viewWidth", bare_ndk_view_width)
  V("viewHeight", bare_ndk_view_height)
  V("viewRootWindowInsets", bare_ndk_view_root_window_insets)
  V("viewLocationInWindow", bare_ndk_view_location_in_window)
  V("viewWindowInsetsController", bare_ndk_view_window_insets_controller)

  V("windowInsetsControllerShow", bare_ndk_window_insets_controller_show)
  V("windowInsetsControllerHide", bare_ndk_window_insets_controller_hide)
  V("viewDefaultFocusHighlight", bare_ndk_view_default_focus_highlight)
  V("viewVisible", bare_ndk_view_visible)
  V("viewAlpha", bare_ndk_view_alpha)
  V("viewTranslationX", bare_ndk_view_translation_x)
  V("viewTranslationY", bare_ndk_view_translation_y)
  V("viewTranslationZ", bare_ndk_view_translation_z)
  V("viewScaleX", bare_ndk_view_scale_x)
  V("viewScaleY", bare_ndk_view_scale_y)
  V("viewRotation", bare_ndk_view_rotation)
  V("viewRotationX", bare_ndk_view_rotation_x)
  V("viewRotationY", bare_ndk_view_rotation_y)
  V("viewPivotX", bare_ndk_view_pivot_x)
  V("viewPivotY", bare_ndk_view_pivot_y)
  V("viewCameraDistance", bare_ndk_view_camera_distance)
  V("viewElevation", bare_ndk_view_elevation)
  V("viewOutlineAmbientShadowColor", bare_ndk_view_outline_ambient_shadow_color)
  V("viewOutlineSpotShadowColor", bare_ndk_view_outline_spot_shadow_color)
  V("viewEnabled", bare_ndk_view_enabled)
  V("viewSetPadding", bare_ndk_view_set_padding)
  V("viewClipToOutline", bare_ndk_view_clip_to_outline)
  V("viewBackground", bare_ndk_view_background)

  V("windowInsetsInsets", bare_ndk_window_insets_insets)

  V("viewGroupAddView", bare_ndk_view_group_add_view)
  V("viewGroupRemoveView", bare_ndk_view_group_remove_view)
  V("viewGroupClipChildren", bare_ndk_view_group_clip_children)

  V("scrollViewInit", bare_ndk_scroll_view_init)
  V("scrollViewEventMask", bare_ndk_scroll_view_event_mask)
  V("viewScrollX", bare_ndk_view_scroll_x)
  V("viewScrollY", bare_ndk_view_scroll_y)
  V("viewScrollTo", bare_ndk_view_scroll_to)
  V("horizontalScrollViewInit", bare_ndk_horizontal_scroll_view_init)

  V("frameGroupInit", bare_ndk_frame_group_init)
  V("frameGroupSetFrame", bare_ndk_frame_group_set_frame)
  V("frameGroupEventMask", bare_ndk_frame_group_event_mask)

  V("textMeasure", bare_ndk_text_measure)
  V("textMeasureSpanned", bare_ndk_text_measure_spanned)

  V("spannableStringBuilderInit", bare_ndk_spannable_string_builder_init)
  V("spannableStringBuilderAppend", bare_ndk_spannable_string_builder_append)
  V("spannableStringBuilderLength", bare_ndk_spannable_string_builder_length)
  V("spannableStringBuilderSetSpan", bare_ndk_spannable_string_builder_set_span)

  V("letterSpacingSpanInit", bare_ndk_letter_spacing_span_init)
  V("underlineSpanInit", bare_ndk_underline_span_init)
  V("strikethroughSpanInit", bare_ndk_strikethrough_span_init)
  V("foregroundColorSpanInit", bare_ndk_foreground_color_span_init)
  V("absoluteSizeSpanInit", bare_ndk_absolute_size_span_init)
  V("typefaceSpanInit", bare_ndk_typeface_span_init)

  V("bitmapFactoryDecodeFile", bare_ndk_bitmap_factory_decode_file)
  V("bitmapWidth", bare_ndk_bitmap_width)
  V("bitmapHeight", bare_ndk_bitmap_height)
  V("bitmapDensity", bare_ndk_bitmap_density)

  V("imageViewInit", bare_ndk_image_view_init)
  V("imageViewSetImageBitmap", bare_ndk_image_view_set_image_bitmap)
  V("imageViewScaleType", bare_ndk_image_view_scale_type)
  V("imageViewImageTint", bare_ndk_image_view_image_tint)

  V("activityThemeColor", bare_ndk_activity_theme_color)

  V("progressBarInit", bare_ndk_progress_bar_init)
  V("progressBarIndeterminate", bare_ndk_progress_bar_indeterminate)
  V("progressBarIndeterminateTint", bare_ndk_progress_bar_indeterminate_tint)

  V("choreographerGetInstance", bare_ndk_choreographer_get_instance)
  V("choreographerPostFrameCallback", bare_ndk_choreographer_post_frame_callback)
  V("choreographerRemoveFrameCallback", bare_ndk_choreographer_remove_frame_callback)

  V("frameCallbackInit", bare_ndk_frame_callback_init)
  V("frameCallbackEventMask", bare_ndk_frame_callback_event_mask)

  V("toggleInit", bare_ndk_toggle_init)
  V("toggleEventMask", bare_ndk_toggle_event_mask)
  V("toggleChecked", bare_ndk_toggle_checked)
  V("toggleNaturalSize", bare_ndk_toggle_natural_size)

  V("editFieldInit", bare_ndk_edit_field_init)
  V("editFieldEventMask", bare_ndk_edit_field_event_mask)
  V("editFieldHint", bare_ndk_edit_field_hint)
  V("editFieldInputType", bare_ndk_edit_field_input_type)
  V("editFieldImeOptions", bare_ndk_edit_field_ime_options)
  V("editFieldSelection", bare_ndk_edit_field_selection)
  V("editFieldFocus", bare_ndk_edit_field_focus)

  V("textViewInit", bare_ndk_text_view_init)
  V("textViewText", bare_ndk_text_view_text)
  V("textViewTextSize", bare_ndk_text_view_text_size)
  V("textViewLineHeight", bare_ndk_text_view_line_height)
  V("textViewMaxLines", bare_ndk_text_view_max_lines)
  V("textViewEllipsize", bare_ndk_text_view_ellipsize)
  V("textViewLineSpacing", bare_ndk_text_view_line_spacing)
  V("textViewTextColor", bare_ndk_text_view_text_color)
  V("textViewTypeface", bare_ndk_text_view_typeface)
  V("textViewGravity", bare_ndk_text_view_gravity)
  V("textViewJustificationMode", bare_ndk_text_view_justification_mode)

  V("typefaceCreate", bare_ndk_typeface_create)
  V("typefaceCreateFromTypeface", bare_ndk_typeface_create_from_typeface)

  V("gradientDrawableInit", bare_ndk_gradient_drawable_init)
  V("gradientDrawableColor", bare_ndk_gradient_drawable_color)
  V("gradientDrawableCornerRadius", bare_ndk_gradient_drawable_corner_radius)
  V("gradientDrawableCornerRadii", bare_ndk_gradient_drawable_corner_radii)
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
#undef R
#undef V

#define V(name, n) \
  { \
    js_value_t *val; \
    err = js_create_int32(env, n, &val); \
    assert(err == 0); \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V("FRAME_CALLBACK_EVENT_FRAME", bare_ndk_frame_callback_event_frame)

  V("TOGGLE_EVENT_CHECKED", bare_ndk_toggle_event_checked)
  V("TOGGLE_EVENT_FOCUS_CHANGED", bare_ndk_toggle_event_focus_changed)

  V("EDIT_FIELD_EVENT_CHANGED", bare_ndk_edit_field_event_changed)
  V("EDIT_FIELD_EVENT_REPLACING", bare_ndk_edit_field_event_replacing)
  V("EDIT_FIELD_EVENT_SELECTION_CHANGED", bare_ndk_edit_field_event_selection_changed)
  V("EDIT_FIELD_EVENT_FOCUS_CHANGED", bare_ndk_edit_field_event_focus_changed)
  V("EDIT_FIELD_EVENT_ACTION", bare_ndk_edit_field_event_action)

  V("FRAME_GROUP_EVENT_SIZE_CHANGED", bare_ndk_frame_group_event_size_changed)
  V("FRAME_GROUP_EVENT_INSETS_CHANGED", bare_ndk_frame_group_event_insets_changed)
  V("FRAME_GROUP_EVENT_CONFIGURATION_CHANGED", bare_ndk_frame_group_event_configuration_changed)
  V("SCROLL_VIEW_EVENT_SCROLL_CHANGED", bare_ndk_scroll_view_event_scroll_changed)

  V("FRAME_GROUP_EVENT_DOWN", bare_ndk_frame_group_event_down)
  V("FRAME_GROUP_EVENT_MOVE", bare_ndk_frame_group_event_move)
  V("FRAME_GROUP_EVENT_UP", bare_ndk_frame_group_event_up)
  V("FRAME_GROUP_EVENT_CANCEL", bare_ndk_frame_group_event_cancel)

  V("WINDOW_INSETS_TYPE_SYSTEM_BARS", bare_ndk__window_insets_type("systemBars"))

  V("DIALOG_INTERFACE_BUTTON_POSITIVE", bare_ndk__dialog_interface_constant("BUTTON_POSITIVE"))
  V("DIALOG_INTERFACE_BUTTON_NEGATIVE", bare_ndk__dialog_interface_constant("BUTTON_NEGATIVE"))
  V("DIALOG_INTERFACE_BUTTON_NEUTRAL", bare_ndk__dialog_interface_constant("BUTTON_NEUTRAL"))

  V("UI_MODE_NIGHT_MASK", bare_ndk__configuration_constant("UI_MODE_NIGHT_MASK"))
  V("UI_MODE_NIGHT_UNDEFINED", bare_ndk__configuration_constant("UI_MODE_NIGHT_UNDEFINED"))
  V("UI_MODE_NIGHT_NO", bare_ndk__configuration_constant("UI_MODE_NIGHT_NO"))
  V("UI_MODE_NIGHT_YES", bare_ndk__configuration_constant("UI_MODE_NIGHT_YES"))

  V("UI_MODE_MANAGER_MODE_NIGHT_AUTO", bare_ndk__ui_mode_manager_constant("MODE_NIGHT_AUTO"))
  V("UI_MODE_MANAGER_MODE_NIGHT_CUSTOM", bare_ndk__ui_mode_manager_constant("MODE_NIGHT_CUSTOM"))
  V("UI_MODE_MANAGER_MODE_NIGHT_NO", bare_ndk__ui_mode_manager_constant("MODE_NIGHT_NO"))
  V("UI_MODE_MANAGER_MODE_NIGHT_YES", bare_ndk__ui_mode_manager_constant("MODE_NIGHT_YES"))
  V("WINDOW_INSETS_TYPE_DISPLAY_CUTOUT", bare_ndk__window_insets_type("displayCutout"))
  V("WINDOW_INSETS_TYPE_IME", bare_ndk__window_insets_type("ime"))
#undef V

  return exports;
}

BARE_MODULE(bare_ndk, bare_ndk_exports)
