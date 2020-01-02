#include <iostream>

#include "../require.h"
using namespace std;

class HasPointer {
    double* p;
public:
    HasPointer(double x){
        p = new double(x);
    }
    HasPointer(const HasPointer& rhs, bool b = true) {
        p = new double(*rhs.p);
        if(b) cout << "copied a " << *p << "\n";
    }
    ~HasPointer(){
        cout << "~HasPointer()\n";
        delete p;
    }
    void print(){
        cout << *p << endl;
    }
};

void f(HasPointer hp) {
    hp.print();
}

int main(int argc, char *argv[])
{
    HasPointer hp1(5);
    f(hp1);
    HasPointer hp2(hp1, false);
    return 0;
}
