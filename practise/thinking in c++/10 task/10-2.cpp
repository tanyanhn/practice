#include <iostream>
#include "../require.h"
using namespace std;

int f(bool t = false) {
    static int a = 1;
    static int b = 1;
    if (t == true) { a = 1; b = 1; return a;}
    a = a + b; b = a - b;
    return a;
}

int main(int argc, char *argv[])
{
    for(int i = 0; i < 20 ; ++i ){
        int j = f();
        cout << j << endl;
    }
    int j = f(1) ;cout << j <<endl;
    return 0;
}
