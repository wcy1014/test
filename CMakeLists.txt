# ##############################################################################
# The minimum version required is CMake 3.15.2
cmake_minimum_required(VERSION 3.15.2)

# ##############################################################################
# set(CONAN "ON")
# load and run external cmake codes using ccache
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(my-test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  set(DEBUG_POSTFIX "d")
  set(CMAKE_DEBUG_POSTFIX ${DEBUG_POSTFIX})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} include src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
if (MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
else ()
  SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CMAKE_CXX_FLAGS} -O0 -g3 -ggdb ")
  SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CMAKE_CXX_FLAGS} -O3  ")
  SET(CMAKE_C_FLAGS_DEBUG "$ENV{CMAKE_C_FLAGS} -O0 -g3 -ggdb ")
  SET(CMAKE_C_FLAGS_RELEASE "$ENV{CMAKE_C_FLAGS} -O3  ")
endif ()

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif()

link_directories(${LINK_SEARCH_PATH})

# ##############################################################################
# build version
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)
message(
  STATUS "my-test Version: ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

configure_file(${CMAKE_SOURCE_DIR}/src/test_version.txt
               ${CMAKE_SOURCE_DIR}/src/version/test.h @ONLY)

set(SHARED_LIB my-test)
set(STATIC_LIB my-test-static)

set(ALOG)
if(MSVC)
  set(THIRD_PARTY)
else()
  set(THIRD_PARTY)
  if (ANDROID)
    set(ALOG log)
  endif() 
endif()

add_subdirectory(src)
add_subdirectory(test)
# add_subdirectory(examples)
