cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)
find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-android REQUIRED PATHS node_modules/cmake-android)
find_package(cmake-prelude REQUIRED PATHS node_modules/cmake-prelude)

project(bare_ndk C CXX)

use_java()

fetch_package("github:holepunchto/bare@1.38.0")
fetch_package("github:holepunchto/libpath#a68d099")
fetch_package("github:holepunchto/libjstl")
fetch_package("github:holepunchto/libjnitl")

add_bare_module(
  bare_ndk
  SOURCES
    binding.cc
  LINK
    jstl
    jnitl
    android
)

target_include_directories(
  ${bare_ndk}
  PRIVATE
    node_modules/bare-jni-registry/lib
)

find_android_stl(android_stl)

find_android_jar(android_jar)

add_dex(
  bare_runtime_classes
  SOURCES
    lib/runtime/Activity.java
  INCLUDE_JARS
    ${android_jar}
)

add_dex(
  bare_ndk_classes
  SOURCES
    lib/Dialog.java
    lib/EditField.java
    lib/FrameCallback.java
    lib/FrameGroup.java
    lib/LetterSpacingSpan.java
    lib/HorizontalScrollGroup.java
    lib/ScrollGroup.java
    lib/Toggle.java
  INCLUDE_JARS
    ${android_jar}
)

add_library_targets(
  bare_runtime
  FEATURES
    c_std_11
    cxx_std_20
  SOURCES
    lib/runtime.cc
  LINK
    PRIVATE
      $<LINK_LIBRARY:WHOLE_ARCHIVE,bare::static>
      bare::exports
      rlimit::static
      path::static
      jnitl
      android
  TYPE SHARED
  EXPORTS
    bare_native_activity
    bare_native_wake
    Java_to_holepunch_bare_Activity_resume
    Java_to_holepunch_bare_Activity_setup
    Java_to_holepunch_bare_Activity_suspend
    Java_to_holepunch_bare_Activity_teardown
  STRIP ON
  INSTALL OFF
  EXPORT OFF
)

set_target_properties(
  bare_runtime_shared
  PROPERTIES
  OUTPUT_NAME bare
)

target_link_options(
  bare_runtime_shared
  PRIVATE
    "-Wl,-z,global"
)

bare_target(target)

bare_module_target("." module NAME name)

install(FILES $<TARGET_FILE:bare_runtime::shared> DESTINATION ${target})

install(FILES ${android_stl} DESTINATION ${target}/bare)

install(
  FILES $<TARGET_PROPERTY:bare_runtime_classes,DEX_FILE>
  DESTINATION ${target}/bare
  RENAME classes.dex
)

install(
  FILES $<TARGET_PROPERTY:bare_ndk_classes,JAR_FILE>
  DESTINATION ${target}/${name}
  RENAME classes.jar
)

install(
  FILES $<TARGET_PROPERTY:bare_ndk_classes,DEX_FILE>
  DESTINATION ${target}/${name}
  RENAME classes.dex
)
