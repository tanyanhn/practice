cmake_minimum_required(VERSION 2.6)
project(Example1)

include(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
check_function_exists(rand RAND_EXISTS)

#Version number
set (VERSION_NUMBER 1)

#configured a header that contains CMake settings
configure_file(
  "${PROJECT_SOURCE_DIR}/ExampleConfig.h.in"
  "${PROJECT_BINARY_DIR}/ExampleConfig.h"
  )

#add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}")

#add custom random number generator
include_directories("${PROJECT_SOURCE_DIR}/Rand")
add_subdirectory(Rand)
set (EXTRA_LIBS ${EXTRA_LIBS} Rand)

add_executable(Example4 example.cpp)
target_link_libraries(Example4 ${EXTRA_LIBS})

include(CTest)
add_test(CheckSeed Example4 0)
set_tests_properties(CheckSeed
  PROPERTIES
  PASS_REGULAR_EXPRESSION
  "3 2 5 4 7 6 1 0"
  )