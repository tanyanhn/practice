#include"cpp_function.hh"

int cpp_function(int *val){
    *val = *val * 5;
    return 377;
}

// fortran wrapper
int cpp_function_(int *val){
    return cpp_function(val);
}