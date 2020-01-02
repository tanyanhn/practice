#include <iostream>
#include "../require.h"
using namespace std;

void f(const int i){
    // i++
    /*8.13.cpp: In function ‘void f(int)’:
    8.13.cpp:6:6: error: increment of read-only parameter ‘i’
    i++;*/
}
int main(int argc, char *argv[])
{
    
    return 0;
}
