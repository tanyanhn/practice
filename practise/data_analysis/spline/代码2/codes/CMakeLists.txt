cmake_minimum_required(VERSION 3.0)

project(PROJECT3_SPLINE)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LAPACKE REQUIRED lapacke)

link_directories("/usr/local/lib")
include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") 

#default compiler
set(CMAKE_C_COMPILER "/usr/bin/gcc") 
set(CMAKE_CXX_COMPILER "/usr/bin/g++") 

add_subdirectory(main)

add_subdirectory(test)

add_subdirectory(doc)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin") 

add_custom_target(runAssignment
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/main
COMMAND ./PROJECT3_ASSIGNMENT
)

add_custom_target(plotAssignment
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/output
COMMENT "All pictures are generated in '/output'."
COMMAND octave B_completePlot.m
COMMAND octave B_notAknotPlot.m
COMMAND octave C_458.m
COMMAND octave C_459.m
COMMAND octave E_heart_10.m
COMMAND octave E_heart_40.m
COMMAND octave E_heart_160.m
COMMAND octave F_beastPlot.m
COMMAND octave G_N1.m
COMMAND octave G_N2.m
)

add_custom_target(cleanOutput
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
COMMAND rm -rf test/*.m
COMMAND rm -rf output/*.m output/*.png
)
