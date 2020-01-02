#include <iostream>

#include "../require.h"
using namespace std;

class A {
    int i;
    A(const A&) {}
public:
    A(){}
    ~A(){
        cout << "~A()\n";
    }
    void print(){
        cout << i << endl;
    }
    A& clone() const {
        A* p = new A;
        return *p;
    }
    void set(int ii) {
        i = ii;
    }
};

A& f(const A& a) {
    A& b = a.clone();
    return b;
}

int main(int argc, char *argv[])
{
    const A a;
    A& b = f(a);
    b.set(4);
    b.print();
    delete &b;
    return 0;
}
