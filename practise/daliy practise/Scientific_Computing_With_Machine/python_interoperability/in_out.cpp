// The header file contains definitions needed to generate the interface
#include <Python.h>
#include <boost/python.hpp>

// This function will be implemented in C++, but called from python.
float sumvals(int array_length, boost::python::numeric::array in){
    float value = 0.0f;
    // Note that before values can be used, they must first be extracted
    // via the boost::python machinery
    for(unsigned int i = 0; i < array_length; i++){
        value += boost::python::extract<float>(in[i]);
    }
    return value;
}

// This is where we declare what C++ functions(s) will appear in python module.
BOOST_PYTHON_MODULE(in_out){
    boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
    def("sumvals", sumvals);
}
