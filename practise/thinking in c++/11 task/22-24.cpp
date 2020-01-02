#include <iostream>

#include "../require.h"
using namespace std;

class A {
public:
    double d;
    A(){}
    ~A(){}
    void print(){
        cout << d << endl;
    }
};

int main(int argc, char *argv[])
{
    A a,* p;
    p = &a;
    double A::*dp;
    dp = &A::d;
    void (A::*fp)();
    fp = &A::print;
    a.*dp = 99.9;
    (p->*fp)();
    return 0;
}
