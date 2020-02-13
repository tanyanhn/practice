#include"head.h"

using namespace std;

//k = 2;

void m(){
    k = 2;
    cout << "m()" << endl;
    cout << k << endl;
    f();
    assert(k == 0 && "in part2.cpp");
}