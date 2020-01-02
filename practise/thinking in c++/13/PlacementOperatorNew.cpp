// Placement with operator new()
#include <cstddef> // Size_t
#include <iostream>
using namespace std;

class X {
    int i;
public:
    X(int ii = 0) : i(ii) {
        cout << "this = " << this << "\n";
    }
    ~X(){
        cout << "X::~X(): " << this << "\n";
    }
    void* operator new(size_t, void* loc) {
        return loc;
    }
    void print(){}
};

int main () {
    int l[10];
    cout << "l = " << l << "\n";
    X* xp = new(l) X(47); // X at location l
    xp->X::~X(); // Explicit destructor call
    // ONLY use with placement!
}
