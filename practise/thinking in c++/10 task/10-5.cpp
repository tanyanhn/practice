#include <iostream>
#include <cassert>
#include "../require.h"
using namespace std;

class Monitor1 {
    int count;

public:
    Monitor1(){count = 0;}
    ~Monitor1(){}
    void incident() {
        ++count;
    }
    void decrement(){
        --count;
    }
    
    void print(){
        cout << count << " incidents\n";
    }

};

class Monitor2 {
    Monitor1* pm;

public:
    Monitor2(Monitor1* p){
        assert(p);
        pm = p;
        pm->incident();
        pm->print();
    }
    ~Monitor2(){
        assert(pm);
        pm->decrement();
        pm->print();
    }
    

};

Monitor1 g_mon;

Monitor2 m(&g_mon);

void f() {
    static Monitor2 m(&g_mon);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 5; ++i)
        f();

    return 0;
}
