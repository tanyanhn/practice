// Hiding overloaded names during inheritance
#include <iostream>
#include <string>
#include "../require.h"
using namespace std;

class Base {
public:
    int f() const {
        cout << "Base::f()\n";
        return 1;
    }
    int f(string) const { return 1; }
    void g() {}
    Base(){}
    ~Base(){}
    void print(){}
};

class Derived1 : public Base {
public:
    void g() const {}
    Derived1(){}
    ~Derived1(){}
    void print(){}
};

class Derived2 : public Base {
public:
    // Redefinition:
    int f() const {
        cout << "Derived2::f()\n";
        return 2;
    }
    Derived2(){}
    ~Derived2(){}
    void print(){}
};

class Derived3 : public Base {
public:
    // Change return type:
    void f() const { cout << "Derived3::f()\n"; }
    Derived3(){}
    ~Derived3(){}
    void print(){}
};

class Derived4 : public Base {
public:
    // Change argument list:
    int f(int) const {
        cout << "Derived4::f()\n";
        return 4;
    }
    Derived4(){}
    ~Derived4(){}
    void print(){}
};

int main(int argc, char *argv[])
{
    string s("hello");
    Derived1 d1;
    int x = d1.f();
    d1.f(s);
    Derived2 d2;
    x = d2.f();
    //! d2.f(s); // string version hidden
    Derived3 d3;
    //! x = d3.f(); // return int version hidden
    Derived4 d4;
    //! x = d4.f(); // f() version hidden
    x = d4.f(1);
    return 0;
}
