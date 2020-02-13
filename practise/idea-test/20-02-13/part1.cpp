#include"head.h"

using namespace std;

//k = 1;

void f(){
    k = 1;
    cout << "f()" << endl;
    cout << k << endl;
    if(k == 1){
        int* i = 0;
        *i = 0;
    }
}

int h(){
    k = 1;
    cout << "h()" << endl;
    cout << k << endl;
}