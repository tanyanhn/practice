#include <iostream>
using namespace std;

class A {
    int i;
public:
    void f() {}
};

class B {
    int i;
public:
    virtual void f() {}
};

class C : public B {
public:
    void f() {}
};

int main() {
    A* a = new A;
    cout << a << ' ' << sizeof(*a) << endl;
    delete a;
    B* b = new B;
    cout << b << ' ' << sizeof(*b) << endl;
    delete b;
    C* c = new C;
    cout << c << ' ' << sizeof(*c) << endl;
    delete c;
}
