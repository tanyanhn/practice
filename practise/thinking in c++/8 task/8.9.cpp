#include <iostream>
#include "../require.h"
using namespace std;

int main(int argc, char *argv[])
{
    double T[] ={3.14,5.03,9.34};
    double* const p = T;
    *p += 10;
    cout << *p <<endl;
    cout << *(p+2) << endl;
    //p = T+2;
    
    
    return 0;
}
