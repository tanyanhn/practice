#include <iostream>
#include <ctime>
using namespace std;

class Derived;
class Base {
    int i;
public:
    void nonvirt();
    virtual void virt();
    friend Derived;
};

void Base::nonvirt() { i = 1;}
void Base::virt() {i = 2;}

class Derived : public Base {
public:
    void virt() ;
};

void Derived::virt() {i = 3;}

double measure(Base* bp, void (Base::* f)()) {
    clock_t start = clock();
    for (int i = 0; i < 10000000L; ++i)
        (bp->*f)();
    clock_t stop = clock();
    return static_cast<double>(stop - start) / CLOCKS_PER_SEC;
}

int main() {
    Derived d;
    cout << measure(&d, &Base::nonvirt) << endl;
    cout << measure(&d, &Base::virt) << endl;
}
