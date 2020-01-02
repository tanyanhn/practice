#include <iostream>

#include "../require.h"
using namespace std;

class A {
    int i;
public:
    A(){}
    ~A(){}
    void print(){}
    void f() const {}
    void g() {}
};

void f1(A a) {
    a.f();
    a.g();
}
void f2(A& a) {
    a.f();
    a.g();
}
void f3(const A& a) {
    a.f();
    // a.g();
}
int main(int argc, char *argv[])
{
    return 0;
}
