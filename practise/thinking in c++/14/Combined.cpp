// Inheritance & composition
#include<iostream>
using namespace std;

class A  {
    int i;
public:
    A(int ii) : i(ii) {
        cout << "A()\n";
    }
    ~A(){
        cout << "A()\n";
    }
    void f() const {}
    void print(){}
};

class B  {
    int i;
public:
    B(int ii) : i(ii) {
        cout << "B()\n";
    }
    ~B(){
        cout << "B()\n";
    }
    void f() const {}
    void print(){}
};

class C : public B {
    A a;
public:
    C(int ii) : B(ii), a(ii) {
        cout << "C()\n";
    }
    ~C(){
        cout << "C()\n";
    } // Calls ~A() and ~B()
    void f() const {// Redefinition
        a.f();
        B::f();
    }
    void print(){}
};

int main() {
    C c(47);
}
