#include <iostream>

#include "../require.h"
using namespace std;

class A {
    int i;

public:
    A(int ii = 0) : i(ii) {}
    ~A(){
        cout << "exit\n";
        exit(1);
    }
    void print(){}

};


A a;

int main(int argc, char *argv[])
{
    cout << "in main\n";
    return 0;
}
