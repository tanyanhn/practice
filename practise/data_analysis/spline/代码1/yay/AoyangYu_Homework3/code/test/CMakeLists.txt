aux_source_directory(. DIR_TEST)

add_executable(test ${DIR_TEST})
target_link_libraries(test lapack)

target_link_libraries(test SplineLib)

# set_target_properties(SplineLib PROPERTIES CXX_STANDARD 17)