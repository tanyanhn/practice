#include <iostream>
#include "../require.h"
using namespace std;

int main(int argc, char *argv[])
{
    int i = 1;
    const int* const p = &i;
    cout << *p << endl;
    //*p = 2;
    //p += 1;
    
    return 0;
}
