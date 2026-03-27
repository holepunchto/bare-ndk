cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)
find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-android REQUIRED PATHS node_modules/cmake-android)

project(bare_android C CXX)

fetch_package("github:holepunchto/bare@1.25.0")
fetch_package("github:holepunchto/libpath")
fetch_package("github:holepunchto/libjstl")
fetch_package("github:holepunchto/libjnitl")

add_bare_module(bare_ndk)

target_sources(
  ${bare_ndk}
  PRIVATE
    binding.cc
)

target_link_libraries(
  ${bare_ndk}
  PUBLIC
    jstl
    jnitl
    android
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

add_library(bare_runtime SHARED)

target_sources(
  bare_runtime
  PRIVATE
    lib/runtime.cc
)

set_target_properties(
  bare_runtime
  PROPERTIES
  C_STANDARD 11
  CXX_STANDARD 20
  POSITION_INDEPENDENT_CODE ON
  OUTPUT_NAME bare
)

target_link_libraries(
  bare_runtime
  PUBLIC
    $<LINK_LIBRARY:WHOLE_ARCHIVE,bare_static>
  PRIVATE
    rlimit_static
    path_static
  PRIVATE
    jnitl
    android
)

target_link_options(
  bare_runtime
  PRIVATE
    "-Wl,-z,global"
)

bare_target(target)

bare_module_target("." module NAME name)

install(TARGETS bare_runtime LIBRARY DESTINATION ${target})

install(
  FILES
    ${android_stl}
    $<TARGET_PROPERTY:bare_runtime_classes,DEX_FILE>
  DESTINATION ${target}/bare
)
