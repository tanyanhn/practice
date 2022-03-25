aux_source_directory("${PROJECT_SOURCE_DIR}/main" DIR_MAIN)
#set(SRC "${PROJECT_SOURCE_DIR}/src" )

include_directories("${PROJECT_SOURCE_DIR}/include")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/main")

add_executable(PROJECT3_ASSIGNMENT
 Assignment.cpp
)

target_link_libraries(
  PROJECT3_ASSIGNMENT
  lapacke
)

# add_test(NAME Spline_test COMMAND "${PROJECT_SOURCE_DIR}/bin/test/Spline_test_cmake")
# set_tests_properties (PolyInterp_test
# PROPERTIES FAIL_REGULAR_EXPRESSION "failed")