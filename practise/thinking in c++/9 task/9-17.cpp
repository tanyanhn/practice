#include <iostream>
#include "../require.h"
using namespace std;

#define TRACE(s) cout << #s << endl;s

int main(int argc, char *argv[])
{
    TRACE(int x);
    TRACE( x = 7);
    cout << x << endl;
    TRACE( ++x );
    cout << x << endl;
    return 0;
}
