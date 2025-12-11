cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)
find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)

project(bare_android C CXX)

fetch_package("github:holepunchto/bare@1.24.5")
fetch_package("github:holepunchto/libpath")
fetch_package("github:holepunchto/libjstl")
fetch_package("github:holepunchto/libjnitl")

find_package(Java)

include(UseJava)

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

set(ANDROID_JAR ${ANDROID_HOME}/platforms/${ANDROID_PLATFORM}/android.jar)

add_jar(
  bare_runtime_classes
  SOURCES
    lib/runtime/Activity.java
  INCLUDE_JARS
    ${ANDROID_JAR}
  OUTPUT_NAME classes
)

find_program(d8 d8 PATHS ${ANDROID_HOME}/build-tools/* NO_DEFAULT_PATH)

add_custom_command(
  TARGET bare_runtime_classes
  POST_BUILD
  COMMAND
    ${d8}
      --release
      --lib ${ANDROID_JAR}
      --output ${CMAKE_BINARY_DIR}
      ${CMAKE_BINARY_DIR}/classes.jar
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
    log_static
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

find_library(
  android_stl
  ${ANDROID_STL}
  PATHS ${CMAKE_SYSROOT}/usr/lib
  PATH_SUFFIXES ${CMAKE_LIBRARY_ARCHITECTURE}
  NO_DEFAULT_PATH
  REQUIRED
)

install(TARGETS bare_runtime LIBRARY DESTINATION ${target})

install(
  FILES
    ${android_stl}
    ${CMAKE_BINARY_DIR}/classes.dex
  DESTINATION ${target}/bare
)
