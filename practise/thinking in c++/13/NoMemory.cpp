// Constructor isn't called if new fails
#include <iostream>
#include <new> //bad_alloc definition
using namespace std;

class NoMemory {
public:
    NoMemory(){
        cout << "NoMemory::NoMemory()" << endl;
    }
    void* operator new(size_t sz) {
        cout << "NoMemory::operator new\n";
        throw bad_alloc(); // "Out of memory"
    }
    ~NoMemory(){}
    void print(){}
};
int main() {
    NoMemory* nm = 0;
    try{
        nm = new NoMemory;
    } catch (bad_alloc) {
        cerr << "Out of memory exception\n";
    }
    cout << "nm = " << nm << endl;
}
