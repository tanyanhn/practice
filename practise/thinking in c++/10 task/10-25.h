#ifndef POLITE_H
#define POLITE_H
#include <iostream>
#include <string>

class Polite {
    std::string data;

public:
    Polite(const std:: string& s) : data(s) {}
    ~Polite(){}
    void print(){
        std::cout << "data == " << data << std::endl;
    }

};
#endif
