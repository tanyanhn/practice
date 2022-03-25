aux_source_directory(. DIR_MAIN)
add_executable(main ${DIR_MAIN})

target_link_libraries(main lapack)
target_link_libraries(main SplineLib)

# set_target_properties(SplineLib PROPERTIES CXX_STANDARD 17)