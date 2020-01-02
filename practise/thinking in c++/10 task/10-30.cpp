#include <iostream>

#include "../require.h"
using namespace std;

struct A
{
private:
    int i;
public:
    A() : i(0) {}
    void print() {
        cout << i << endl;
    }
};

void f(){
    A a;
    a.print();
}

int main(int argc, char *argv[])
{
    f();
    return 0;
}
