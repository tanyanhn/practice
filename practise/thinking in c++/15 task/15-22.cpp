#include <iostream>
using namespace std;

class Base {
public:
    virtual void f() {
        cout << "Base::f()\n";
    }
    virtual int f(int) {
        cout << "Base::f(int)\n";
    }
    virtual char f(char) {
        cout << "Base::f(char)\n";
    }
};

class Derived : public Base {
public:
    void f() {
        cout << "Derived::f()\n";
        }
};

int main() {
    Derived d;
    d.Base::f();
    Base* b = static_cast<Base*>(&d);
    b->f();b->f(1);b->f('a');
    // d.f(1);
    d.f();
}
