#include <iostream>

#include "../require.h"
using namespace std;

class Inner {
    double x;
public:
    Inner(double x){
        this->x = x;
    }
    Inner(const Inner& i2) {
        x = i2.x;
        cout << "Inner::Inner(const Inner&)\n";
    }
    double getX() const {
        return x;
    }
    ~Inner(){}
    void print(){}
};

class Outer {
    Inner m;
    int n;
public:
    Outer(double x, int i) : m(x), n(i) {}
    ~Outer(){}
    void print(){
        cout << '(' << m.getX() << ',' << n << ")\n";
    }
};

int main(int argc, char *argv[])
{
    Outer o1(10.0, 20);
    o1.print();
    Outer o2(o1);
    o2.print();
    return 0;
}
