## How to Build and Run

The writer of these code has the following working environment:

* Arch Linux
* g++ (GCC) 11.1.0 (C++17)
* Lapack 3.10.0 **shared library**
* CMake 3.21.4
* GNU Make 4.3
* Catch2 2.13.7 (a lightweight testing framework)
  + This library need *not* to be installed, because it is a header-only library.
    Include the header `test/catch.hpp` and everything is OK.

To build the project, first go into the `build` directory (which should be empty for a fresh uncompression) and then type `cmake ..`. Keep in the `build` directory.

* To build the main program, type `make main`. Type `./main/main` to execute it.
* To build the test, type `make test`. Type `./test/test` to execute it.
* Type `make` to build both.

## Interpreting the Results

The results has clear meaning in the context of homework 3, so it would be easy to interpret them.
