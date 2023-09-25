# ##############################################################################
# source file

file(GLOB_RECURSE ALL_HEADER "${CMAKE_SOURCE_DIR}/include//*.h")
file(GLOB_RECURSE ALL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.c*"
     "${CMAKE_CURRENT_SOURCE_DIR}/*.h*")
source_group(
  TREE "${CMAKE_SOURCE_DIR}/include/"
  PREFIX "Header Files"
  FILES ${ALL_HEADER})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Source Files"
  FILES ${ALL_SOURCE})

add_library(${STATIC_LIB} STATIC ${ALL_HEADER} ${ALL_SOURCE})
add_library(${SHARED_LIB} SHARED ${ALL_HEADER} ${ALL_SOURCE})

add_definitions(-DTEST_LIB)
target_compile_definitions(${SHARED_LIB} PUBLIC -DTEST_DLL)

file(GLOB CHECK_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.c*"
     "${CMAKE_CURRENT_SOURCE_DIR}/data-cache-center/*.h*")

if(MSVC)
  set_source_files_properties(${CHECK_SRC} PROPERTIES COMPILE_FLAGS
                                                      "/W4 /WX /EHsc")
  set_source_files_properties(${ALL_HEADER} ${ALL_SOURCE}
                              PROPERTIES COMPILE_FLAGS "/EHsc")
elseif(${PLATFORM_ANDROID})
  set_source_files_properties(${CHECK_SRC} PROPERTIES COMPILE_FLAGS
                                                      "-Wall -Wextra -pedantic")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -fvisibility=hidden")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -fvisibility=hidden")
elseif(APPLE)
  set_source_files_properties(
    ${CHECK_SRC} PROPERTIES COMPILE_FLAGS "-Wall -Wextra -pedantic -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -fvisibility=hidden")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -fvisibility=hidden")
  set(SYMBOL_FILE "${CMAKE_CURRENT_SOURCE_DIR}/TEST_EXPORT.map")
  set_property(TARGET ${SHARED_LIB} APPEND_STRING PROPERTY LINK_FLAGS " -Wl,-exported_symbols_list,${SYMBOL_FILE}")
else()
  set_source_files_properties(
    ${CHECK_SRC} PROPERTIES COMPILE_FLAGS "-Wall -Wextra -pedantic -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -fvisibility=hidden")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -fvisibility=hidden")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/TEST_EXPORT.map")
endif()

target_link_libraries(${SHARED_LIB} ${THIRD_PARTY} ${ALOG})

# ##############################################################################
# install configuration
message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

set(ORIGIN_NAME
    ${SHARED_LIB}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
set(ORIGIN_OUT
    ${CMAKE_SHARED_LIBRARY_PREFIX}${ORIGIN_NAME}${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}
)
set(ALIAS_OUT
    ${CMAKE_SHARED_LIBRARY_PREFIX}${SHARED_LIB}${CMAKE_DEBUG_POSTFIX}${CMAKE_SHARED_LIBRARY_SUFFIX}
)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/output/test)
if(MSVC)
  install(
    TARGETS ${SHARED_LIB}
    RUNTIME DESTINATION ${OUTPUT_DIR}/bin
    LIBRARY DESTINATION ${OUTPUT_DIR}/lib
    ARCHIVE DESTINATION ${OUTPUT_DIR}/lib)
else()
  install(TARGETS ${SHARED_LIB} DESTINATION ${OUTPUT_DIR}/lib)
endif()
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/test
        DESTINATION ${OUTPUT_DIR}/include)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/common
        DESTINATION ${OUTPUT_DIR}/include/test)
