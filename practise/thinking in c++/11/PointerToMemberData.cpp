#include <iostream>

#include "../require.h"
using namespace std;

class Data {
public:
    int a, b, c;
    Data(){}
    ~Data(){}
    void print()const {
        std::cout << "a = "<< a << ", b = " << b  << ", c = " << c << std::endl;
    }
};

int main(int argc, char *argv[])
{
    Data d, *dp = &d;
    int Data::*pmInt;
    pmInt = &Data::a;
    dp->*pmInt = 47;
    pmInt = &Data::b;
    d.*pmInt = 48;
    pmInt = &Data::c;
    dp->*pmInt = 49;
    dp->print();
    return 0;
}
