#include <iostream>
#include "../require.h"
using namespace std;

int main(int argc, char *argv[])
{
    long A[4] = {10 ,3 ,90 ,3};
    const long int* p = A;
    const long int* q = A+1;
    cout << *(p+1) <<endl << *(q+3) <<endl;
    //*(q+1) = 30;
    
    return 0;
}
