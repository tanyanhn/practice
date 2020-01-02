#include <iostream>

#include "../require.h"
using namespace std;

class A {
    int i;
public:
    A(int ii = 0) : i(ii){
        cout << "A()" << endl;
    }
    ~A(){
        cout << "~A()" << endl;
    }
    void print() const {
        cout << i << endl;
    }
    void set(int ii)  {
        i = ii;
    }
};

A f() {
    A a;
    return a;
}

void g( const A& a) {
    a.print();
    // a.set(10);
    a.print();
}


int main(int argc, char *argv[])
{
    g(f());
    return 0;
}
