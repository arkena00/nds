function(project_nds_release)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)

  add_definitions(
  )

  set(INCLUD_DIRS 
    include
  )
  include_directories(${INCLUD_DIRS})

  set(SRC 
    source/main.cpp
    source/nds/data.cpp
    source/nds/nds.cpp
  )
  add_executable( nds_release ${SRC})
  set_target_properties( nds_release 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Projet/nk/nds/bin"
    LIBRARY_OUTPUT_DIRECTORY "C:/Projet/nk/nds/bin"
    RUNTIME_OUTPUT_DIRECTORY "C:/Projet/nk/nds/bin"
    OUTPUT_NAME  "nds"
  )
endfunction(project_nds_release)
project_nds_release()
