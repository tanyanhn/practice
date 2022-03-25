按照下面步骤在本目录/codes下操作
mkdir build
cd build
cmake ..
make
make runAssignment
make plotAssignment #此步依赖于前一步#
make doc #此步依赖于前两步#

之后，在/codes/doc中阅读pdf即可
清理方式为 make cleanOuput 与 make cleanDoc。

附：
Tree View of Codes
codes
├── bin
│   ├── main
│   │   └── PROJECT3_ASSIGNMENT
│   └── test
│       ├── TEST_CARDINAL_CMAKE
│       └── TEST_SPLINE_CMAKE
├── build
│   ├──(...)
│
├── CMakeLists.txt
├── doc
│   ├── CMakeLists.txt
│   └── doc.tex
├── include
│   ├── CardinalBspline.H
│   ├── Config.H
│   ├── InterpConditions.H
│   ├── NewtonInterp_Portable.H
│   ├── Polynomial.H
│   ├── Spline.H
│   ├── TriangleTable.H
│   └── Vec.h
├── main
│   ├── Assignment.cpp
│   ├── CMakeLists.txt
│   └── SnippetsForAssignment.cpp
├── output
│   ├──(...)
│
├── readme.md
└── test
    ├── CMakeLists.txt
    ├── testCardinal.cpp
    ├── testNewton_P.cpp
    ├── testPolty.cpp
    └── testSpline.cpp
$\textbf{bin}$ stores compiled files;\\
$\textbf{doc}$ stores the same document as this one;\\
$\textbf{include}$ stores sources files that support spline implementation;\\
$\textbf{main}$ stores files concerning the assignments;\\
$\textbf{output}$ stores all results such as $\textbf{*.m}$ and $\textbf{*.png}$.
$\textbf{test}$ stores all test files when coding this project.\\

