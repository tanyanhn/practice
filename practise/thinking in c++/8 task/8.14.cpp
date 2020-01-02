#include <iostream>
#include "../require.h"
using namespace std;

void f (float f)
{
    const float& h = f;
    h+1;
}
int main(int argc, char *argv[])
{
    float g = 3.14;
    f(g);
    cout << g << endl;
    
    return 0;
}
