#ifndef DEPENDENCY1_H
#define DEPENDENCY1_H
#include <iostream>

class Dependency1 {
    bool init;
public:
    Dependency1() : init(true)  {
        std::cout << "Dependecy1 construction"
                  << std::endl;
    }
    void print() const {
        std::cout  << "Dependecy1 init : "
                   << init << std::endl;
    }
};
#endif
