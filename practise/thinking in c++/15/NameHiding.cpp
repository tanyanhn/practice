#include <iostream>
#include <string>
using namespace std;

class Base  {
public:
    virtual int f() const {
        cout << "Base::f()\n";
    }
    virtual void f(string) const {    }
    virtual void g() const {}
    Base(){}
    ~Base(){}
    void print(){}
};

class Derived1 : public Base {
public:
    void g() const {}
};

class Derived2 : public Base {
public:
    // Overriding a virtual function:
    int f() const {
        cout << "Derived2::f()\n";
        return 2;
    }
};

class Derived3 : public Base {
public:
    // Cannot change return type:
    //! void f() const { cout << "Derived3::f()\n"; }
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

int main() {
    string s("Hello");
    Derived1 d1;
    int x = d1.f();
    d1.f(s);
    Derived2 d2;
    x = d2.f();
    //! d2.f(s);
    Derived4 d4;
    //! x = d4.f();
    //! d4.d(s);
    Base& br = d4;
    //! br.f(1);
    br.f();
    br.f(s);
}
