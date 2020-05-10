cmake_minimum_required(VERSION 3.7)

project(test_nds)

add_library(lib_gtest OBJECT ${NDS_THIRD_PARTY_ROOT}/gtest/source/gtest-all.cc)
set(GTEST_LIB $<TARGET_OBJECTS:lib_gtest>)

include_directories(${NDS_THIRD_PARTY_ROOT}/gtest/include ${NDS_ROOT}/include)

file(GLOB_RECURSE SOURCES "source/*.cpp")
add_executable(test_nds ${SOURCES})
add_dependencies(test_nds lib_gtest)
target_link_libraries(test_nds ${GTEST_LIB})


set_target_properties(test_nds PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${NDS_BIN_ROOT}/test"
        OUTPUT_NAME  "test_nds")

add_test(NAME test_nds COMMAND "${NDS_BIN_ROOT}/test/test_nds")