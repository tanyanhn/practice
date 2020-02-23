# CMake generated Testfile for 
# Source directory: /home/yan/Desktop/svn/git/practise/daliy practise/Scientific_Computing_With_Machine/cmake/src
# Build directory: /home/yan/Desktop/svn/git/practise/daliy practise/Scientific_Computing_With_Machine/cmake/src/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(CheckSeed "Example4" "0")
set_tests_properties(CheckSeed PROPERTIES  PASS_REGULAR_EXPRESSION "3 2 5 4 7 6 1 0")
subdirs("Rand")
