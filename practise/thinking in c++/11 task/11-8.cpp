#include <iostream>

#include "../require.h"
using namespace std;

void f(char& c) {
    c++;
}

int main(int argc, char *argv[])
{
    char a = 'a';
    cout << a << endl;
    f(a);
    cout << a << endl;
    return 0;
}
