#include <iostream>
using namespace std;

class Base{
public:
    static void f() {
        cout << "Base::f()\n";
    }
    static void g() {
        cout << "Base::g()\n";
    }
    Base(){}
    ~Base(){}
    void print(){}
};

class Derived : public Base {
public:
    static void g(int) {
        cout << "Derived::g(int)\n";
    }
    Derived(){}
    ~Derived(){}
    void print(){}
};

int main() {
    Derived::f();
    Derived::g(1);
     Derived::g(); // Error: too few parameters
}
