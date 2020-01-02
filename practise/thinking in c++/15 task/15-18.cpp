#include <iostream>
using namespace std;

class Base {
    int x;
};

class Derived : public Base {
    float y;
};

void mySize(Base b) {
    cout << "mySize == " << sizeof b << "\n";
}

int main() {
    Base b;
    Derived d;
    cout << "sizeof b == " << sizeof b << "\n";
    cout << "sizeof d == " << sizeof d << "\n";
    mySize(b);
    mySize(d);
}
