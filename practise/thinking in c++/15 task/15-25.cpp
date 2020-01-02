#include <iostream>
using namespace std;

class Base {
public:
    virtual ~Base(){}
    virtual Base* clone() const {
        return new Base(*this);
    }
    virtual void f() {
        cout << "Base::f()\n";
    }
};

class Derived : public Base {
public:
    virtual Derived* clone() const {
        return new Derived(*this);
    }
    virtual void f() {
        cout << "Derived::f()\n";
    }
};

int main() {
    Derived d;
    Base* b = d.clone();
    d.f();
    b->f();
    b->Base::f();
    Base* b2 = d.Base::clone();
    b2->f();
}
