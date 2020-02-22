#include<iostream>
//#include"c_function.h"
#include"cpp_function.hh"
#include"MyCPPClass.hh"

// non-CPP function must declared with C-style linkage
extern "C"
{
    int c_function(int*);
    int fortran_function_(int*);
}

int main(){
    int val = 1;
    int return_val;
    std::cout << "Running CPP program with val = " << val << std::endl;

    // call c_function
    return_val = c_function(&val);
    std::cout << "c_function returns val = " << val << std::endl;
    std::cout << "c_function returns return_val = " << return_val << std::endl;

    // call fortran_function
    return_val = fortran_function_(&val);
    std::cout << "fortran_function returns val = " << val << std::endl;
    std::cout << "fortran_function returns return_val = " << return_val << std::endl;

    std::cout << "CPP program complete.\n" << "\n";
    return 0;
}