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