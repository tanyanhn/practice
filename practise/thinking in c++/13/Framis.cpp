// Local overloaded new & delete
#include <iostream>
#include <cstddef> // Size_t
#include <fstream>
#include <new>
#include "../require.h"
using namespace std;
ofstream out("Framis.out");

class Framis {
    static const int sz = 10;
    char c[sz]; // To take up space, not used
    static unsigned char pool[];
    static bool alloc_map[];
public:
    static const int psize = 100; // frami allowed
    Framis(){ out << "Framis()\n";}
    ~Framis(){out << "~Framis() ..."; }
    void* operator new(size_t) /*throw(bad_alloc)*/;
    void operator delete(void*);
    void print(){}
};
unsigned char Framis::pool[psize * sizeof(Framis)];
bool Framis::alloc_map[psize] = {0};
// Size is ignored -- assume a Framis object
void* Framis::operator new(size_t)
// throw(bad_alloc)
{
    for(int i = 0; i < psize; i++)
        if(!alloc_map[i]) {
            out << "using block " << i << " ... ";
            alloc_map[i] = true; // Mark it used
            return pool + (i * sizeof(Framis));
        }
    out << "out of memory" << endl;
    throw bad_alloc();
}

void Framis::operator delete(void* m) {
    if(!m) return; // Check for null pointer
    // Assume it was created in the pool
    //calculate which block number it is:
    unsigned long block = (unsigned long)m - (unsigned long)pool;
    block /= sizeof(Framis);
    out << "freeing block " << block << endl;
    // Mark it free:
    alloc_map[block] = false;
}

int main(int argc, char *argv[])
{
    Framis* f[Framis::psize];
    try{
        for(int i = 0; i < Framis::psize; i++)
            f[i] = new Framis;
        new Framis; // Out of memory
    }catch(bad_alloc) {
        cerr << "Out of memory!" << endl;
    }
    cout << f[10] << endl;
    delete f[10];
    f[10] = 0;
    // Use relesed memory:
    Framis* x = new Framis;
    cout << x << endl;
    delete x;
    for(int j = 0; j < Framis::psize; j++)
        delete f[j];
    return 0;
}
