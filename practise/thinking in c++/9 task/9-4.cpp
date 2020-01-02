#include <iostream>
#include <ctime>
#include "../require.h"
using namespace std;

void f1(){
    int i = 1;
    float x = i;
    i =static_cast<int>(x);
}

inline void f2() {
    int i = 1;
    float x = i;
    i =static_cast<int>(x);
}

int main(int argc, char *argv[])
{
    clock_t start =clock();
    for (int i = 0; i < 10000000; ++i)
        f1();
    clock_t stop = clock();
    float ticks = stop - start;
    cout << "Time for f1: " << ticks / CLOCKS_PER_SEC << endl;

    start =clock();
    for (int i = 0; i < 10000000; ++i)
        f2();
    stop = clock();
    ticks = stop - start;
    cout << "Time for f2: " << ticks / CLOCKS_PER_SEC << endl;
    return 0;
}
