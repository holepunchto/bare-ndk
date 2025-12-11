#pragma once

#include <assert.h>
#include <bare.h>
#include <jnitl.h>
#include <js.h>

struct bare_ndk_view_t {
  java_global_ref_t<java_object_t<"android/view/View">> handle;
};
