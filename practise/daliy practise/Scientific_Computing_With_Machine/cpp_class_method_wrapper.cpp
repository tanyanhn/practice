#include "cpp_class_method_wrapper.hh"
#include "MyCPPClass.hh"

int cpp_class_method_wrapper(int *val){
    return MyCPPClass::MyCPPClassMethod(val);
}

int cpp_class_method_wrapper_(int *val){
    return MyCPPClass::MyCPPClassMethod(val);
}