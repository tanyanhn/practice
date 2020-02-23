#include "ExampleConfig.h"
#ifdef RAND_EXISTS
#include <cstdlib>
#endif
#include"myrand.h"


int myrand(){
#ifdef RAND_EXISTS
    return rand();
#else
    static int x;
    x = (x * 5 + 3) % (RAND_MAX + 1);
    return x;
#endif
}

void smyrand(int n){
#ifdef RAND_EXISTS
    return srand(n);
#else
    for(int i = 0; i < n; i++)
        myrand();
#endif
}