#include <iostream>
#include <string>
#include "../require.h"
using namespace std;

class A {
    string s;

public:
    A(const char* c = "") : s(c) {}
    ~A(){}
    void print() const {
        cout << "string : " << s << "\n";
    }

};

class B {
    static const int max = 2;
    A a[max];
    const A b[max];
    static A c[max];
    static const A d[max];

public:
    B();
    ~B(){}
    void print(){
        for(int i = 0; i < max; i++){
            cout << "a string : "; a[i].print(); cout << "\n"
                 << "b string : "; b[i].print(); cout << "\n";
            cout << "c string : "; c[i].print(); cout << "\n"
                 << "d string : "; d[i].print(); cout << "\n";
        }
    }

};

const char* x[] ={"tan ", "yan!"};
const char* y[] ={"Hello ", "World."};

B::B() : a{x[0], x[1]}, b{y[0], y[1]} {}

A B::c[]{x[0], y[1]};
const A B::d[] { x[1] , y[0]}; 

int main(int argc, char *argv[])
{
    B b;
    b.print();
    
    return 0;
}
