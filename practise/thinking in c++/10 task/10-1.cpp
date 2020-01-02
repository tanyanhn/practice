#include <iostream>
#include "../require.h"
using namespace std;

int A[5] ={ 1,2,3,4,-1};

int f(int i = 0) {
    static int* p = A;
    if (i != 0) p = A;
    if ( i == 0) {
        if( *p == -1) {cout << "at end";p = A;return -1;}}
    return *(p++);
}
int main(int argc, char *argv[])
{
    int j;
    for (int i = 0 ; i < 19;++i ) {j = f(); cout << j <<endl;}
    j = f(1); cout << j << endl;
    j = f(); cout << j << endl;
    return 0;
}
