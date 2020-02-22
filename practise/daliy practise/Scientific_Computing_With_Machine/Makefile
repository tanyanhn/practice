#! /usr/bin/env make

default:
	@echo "No target specified"

exectables: c_program fortran_program cpp_program

run: exectables
	@echo
	./c_program
	./fortran_program
	./cpp_program

clean:
	rm -f *.o *_program

c_function.o: c_function.c c_function.h
	gcc -c c_function.c

fortran_function.o: fortran_function.f90
	gfortran -c fortran_function.f90

cpp_function.o: cpp_function.cpp cpp_function.hh
	g++ -c cpp_function.cpp

cpp_class_method_wrapper.o: cpp_class_method_wrapper.cpp \
cpp_class_method_wrapper.hh
	g++ -c cpp_class_method_wrapper.cpp

MyCPPClass.o: MyCPPClass.cpp MyCPPClass.hh
	g++ -c MyCPPClass.cpp

function_object_files: c_function.o fortran_function.o cpp_function.o \
                       cpp_class_method_wrapper.o MyCPPClass.o

c_program.o: c_program.c
	gcc -c c_program.c

c_program: c_program.o function_object_files
	gcc c_program.o c_function.o fortran_function.o cpp_function.o \
cpp_class_method_wrapper.o MyCPPClass.o -o c_program

fortran_program.o: fortran_program.f90
	gfortran -c fortran_program.f90

fortran_program: fortran_program.o function_object_files
	gfortran fortran_program.o c_function.o fortran_function.o \
cpp_function.o cpp_class_method_wrapper.o MyCPPClass.o -o fortran_program

cpp_program.o: cpp_program.cpp
	g++ -c cpp_program.cpp

cpp_program: cpp_program.o function_object_files
	g++ cpp_program.o c_function.o fortran_function.o cpp_function.o\
 MyCPPClass.o -o cpp_program
