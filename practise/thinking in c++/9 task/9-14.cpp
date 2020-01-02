#include <iostream>
#include "../require.h"
using namespace std;

class A {
    int a;
public:
    A(int i = 1) : a(i) {cout << "A()\n";}
};

class B {
    A b;
public:
    B(int j = 3) : b(j) {cout << "B()\n";}
} ;
int main(int argc, char *argv[])
{
    B r[5];
    return 0;
}
