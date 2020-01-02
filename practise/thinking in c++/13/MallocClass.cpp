// Malloc with class objects
// What you'd have to do if not for "new"
#include <iostream>
#include <cstdlib> // malloc() & free()
#include <cstring> // memset()
#include "../require.h"
using namespace std;

class Obj {
    int i, j, k;
    static const int sz = 100;
    char buf[sz];
public:
    void initialize() { // Can't use constructor
        cout << "intitializing Obj" << endl;
        i = j= k = 0;
        memset (buf, 0, sz);
    }
    void destroy() const { // Can't use destructor
        cout <<"destroying Obj" << endl;
    }
};


int main(int argc, char *argv[])
{
    Obj* obj = (Obj*)malloc(sizeof(Obj));
    require( obj != 0);
    obj->initialize();
    // ... sometime later:
    obj->destroy();
    free(obj);
    return 0;
}
