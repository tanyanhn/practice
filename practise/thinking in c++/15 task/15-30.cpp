#include <iostream>
using namespace std;

class A {
public:
    virtual void f() {
        cout << "A::f()\n";
    }
};

class B : public A {
private:
    void f() {
        cout << "B::f()\n";
    }
};

void g(A a) {
    A* b1 = &a;
    b1->f();
}

int main() {
    B b;
    // b.f();
    A* b2 = &b;
    b2->f();
    g(b);
}
