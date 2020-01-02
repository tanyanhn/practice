#include <iostream>

#include "../require.h"
using namespace std;

class HasPointer {
    double* p;
public:
    HasPointer(double x){
        p = new double(x);
    }
    /*HasPointer(const HasPointer& rhs) {
        p = new double (*rhs.p);
        cout << "HasPointer(const HasPointer&)\n";
        }*/
    ~HasPointer(){
        cout << *p <<"~HasPointer\n" ;
        *p = -1;
        delete p;
        
    }
    void print(){
        cout << *p << endl;
    }
};

void f(HasPointer hp){
    hp.print();
}

int main(int argc, char *argv[])
{
    HasPointer hp(5);
    f(hp);
    return 0;
}
