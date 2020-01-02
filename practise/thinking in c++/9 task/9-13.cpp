#include <iostream>
#include "../require.h"
using namespace std;

class work {
    int i;
    float j;
public:
    work(int ii , float jj) : i(ii), j(jj){}
    void f1() {
        print();
        f2();
        print();}
    void f2() {
        i = i * j;
        j = j * i;
    }
    void print() const {
        cout << i << " " << j << endl;
    }
};
int main(int argc, char *argv[])
{
    work w(5, 3.14);
    w.f1();
    return 0;
}
