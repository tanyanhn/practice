aux_source_directory("${PROJECT_SOURCE_DIR}/test" DIR_TESTS)
#set(SRC "${PROJECT_SOURCE_DIR}/src" )

include_directories("${PROJECT_SOURCE_DIR}/include")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/test")

add_executable(TEST_SPLINE_CMAKE
 testSpline.cpp
)

target_link_libraries(
  TEST_SPLINE_CMAKE
  lapacke
)

add_executable(TEST_CARDINAL_CMAKE
 testCardinal.cpp
)

target_link_libraries(
  TEST_CARDINAL_CMAKE
  lapacke
)

# add_test(NAME Spline_test COMMAND "${PROJECT_SOURCE_DIR}/bin/test/Spline_test_cmake")
# set_tests_properties (PolyInterp_test
# PROPERTIES FAIL_REGULAR_EXPRESSION "failed")