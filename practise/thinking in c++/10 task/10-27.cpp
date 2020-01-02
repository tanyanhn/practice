#include <iostream>

#include "../require.h"
using namespace std;

class one {
    int i;

public:
    one(int ii = 0) : i(ii) {}
    ~one(){}
    void print(){
        cout << i << endl;
    }

};

class two {
    static one a;

public:
    two() {}
    ~two(){}
    static void print(){
        a.print();
    }

};

one b(4);
one two::a = b;

int main(int argc, char *argv[])
{
    two::print();
    return 0;
}
