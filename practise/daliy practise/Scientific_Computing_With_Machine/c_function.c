#include "c_function.h"

int c_function(int* val){
    *val = *val * 2;
    return 5;
}

// Fortran wrapper
int c_function_(int* val){
    return c_function(val);
}