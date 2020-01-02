#include <iostream>

#include "../require.h"
using namespace std;

class Ipoint {
    int *p;
public:
    Ipoint(int i = 3) {
        p = new int(i); 
    }
    ~Ipoint(){ delete p;}
    void print(){
        cout << 'p' << *p << endl;
    }
    int* pl() {
        return p;
    }
    Ipoint& operator=(const Ipoint& b) {
        int* q = new int;
        *q = *(b.p);
        p = q;
        return *this;
    }
};

int main(int argc, char *argv[])
{
    Ipoint a,b(9);
    a.print();b.print();
    b = a;
    if (a.pl() == b.pl()) cout <<"same point" << "\n";
    else cout << "different point" << "\n";
    return 0;
}
