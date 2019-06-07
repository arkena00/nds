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

add_library(lib_nds OBJECT ${NDS_SOURCES})
target_include_directories(lib_nds PUBLIC "include")

set(NDB_ENGINE_SQLITE ON)
add_subdirectory(third_party/ndb)

add_subdirectory(experimental)
add_subdirectory(benchmark)

