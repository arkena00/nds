cmake_minimum_required(VERSION 3.12)

project(nds)

set(NDS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(NDS_BIN_ROOT ${NDS_ROOT}/bin)
set(NDS_THIRD_PARTY_ROOT ${NDS_ROOT}/third_party)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE NDS_SOURCES
        "${PROJECT_SOURCE_DIR}/include/nds/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/nds/*.tpp"
        "${PROJECT_SOURCE_DIR}/source/nds/*.cpp")

add_library(lib_nds_object OBJECT ${NDS_SOURCES})
target_include_directories(lib_nds_object PUBLIC "include")

add_library(lib_nds INTERFACE)
target_link_libraries(lib_nds INTERFACE lib_nds_object $<TARGET_OBJECTS:lib_nds_object>)

if (NDS_EXPERIMENTAL)
    add_subdirectory(experimental)
endif ()

if (NDS_BENCHMARK)
    add_subdirectory(benchmark)
endif ()