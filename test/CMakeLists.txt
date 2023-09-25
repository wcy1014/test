if(${PLATFORM_LINUX})
  set(CMAKE_CXX_FLAGS_DEBUG
      "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall --coverage -fprofile-arcs -ftest-coverage"
  )
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -lgcov")
endif()
message(STATUS "cxx flags: ${CMAKE_CXX_FLAGS_DEBUG}")

file(GLOB TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/*.h*"
     "${CMAKE_SOURCE_DIR}/include/*.h*")
add_executable(unittest ${TEST_FILES})

if(MSVC)
  set(SYS_LIB)
else()
  set(SYS_LIB dl)
endif()

target_link_libraries(unittest ${STATIC_LIB} ${THIRD_PARTY} ${ALOG} ${SYS_LIB})
