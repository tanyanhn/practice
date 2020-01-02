#include <iostream>

#include "../require.h"
using namespace std;
int y;
int& r =y;

const int& q = 12;

int x = 0;
int& a = x;


int main(int argc, char *argv[])
{
    cout << "x = " << x << ", a = " << a << endl;
    a++;
    cout << "x = " << x << ", a = " << a << endl;
    return 0;
}
