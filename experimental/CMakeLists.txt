cmake_minimum_required(VERSION 3.12)

project(nds)

function(exp_make target_file)
    set(targetname exp_${target_file})

    add_executable(${targetname} ${target_file}.cpp)

    target_link_libraries(${targetname} lib_nds)
    add_dependencies(${targetname} lib_nds)
    set_target_properties(${targetname} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${NDS_BIN_ROOT}/experimental"
            OUTPUT_NAME  ${target_file})

endfunction()

exp_make(encoder)
exp_make(graph)
exp_make(graph_type)
exp_make(graph_bfs)
exp_make(graph_struct)


exp_make(graph2)


exp_make(graph_ndb)
target_link_libraries(exp_graph_ndb lib_ndb)


include_directories(graph_ndb PRIVATE ../../ndb/include)
include_directories(graph_ndb PRIVATE ../../ndb/third_party/sqlite/include)
include_directories(graph_ndb PRIVATE ../../ndb/third_party/boost/)