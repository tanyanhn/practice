#include <iostream>

#include "../require.h"
using namespace std;

class A  {
public:
    A(){ cout << "A()\n";}
    ~A(){ cout << "~A()\n";}
    void print(){}
};

class B  {
public:
    B(){ cout << "B()\n";}
    ~B(){ cout << "~B()\n;";}
    void print(){}
};

class C : public A {
    B b;
public:
    C(){cout << "C()\n";}
    ~C(){ cout << "~C()\n";}
    void print(){}
};

int main() {
    C c;
}
