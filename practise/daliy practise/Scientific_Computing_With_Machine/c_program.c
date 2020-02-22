#include "c_function.h"
#include<stdio.h>

int fortran_function_(int* val);
int cpp_function(int* val);
int cpp_class_method_wrapper(int* val);

int main(){
    int val = 11;
    int return_val;
    return_val = fortran_function_(&val);
    printf("fortran_function returns with val = %d\n", val);
    printf("fortran_function returns with return_val = %d\n", return_val);
    return_val = cpp_function(&val);
    printf("cpp_function returns with val = %d\n", val);
    printf("cpp_function returns with return_val = %d\n", return_val);
    return_val = cpp_class_method_wrapper(&val);
    printf("cpp_class_method returns with val = %d\n", val);
    printf("cpp_class_method returns with return_val = %d\n", return_val);
    printf("C program complete.\n");
    return 0;
}