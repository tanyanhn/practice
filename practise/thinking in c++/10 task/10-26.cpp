#include <iostream>

#include "../require.h"
using namespace std;
class me {
    static double d;
    static long l;

public:
    me(){}
    ~me(){}
    static void print(){
        cout << d << endl << l << endl;
    }

};
double me::d = 3.14;
long me::l = 3.1;

int main(int argc, char *argv[])
{
    me::print();
    return 0;
}
