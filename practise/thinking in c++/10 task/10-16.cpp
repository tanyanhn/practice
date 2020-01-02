#include "10-16.2.h"
#include <iostream>

#include "../require.h"
using namespace std;

namespace t = tan;

void t::print() {
    cout << 10 <<endl;
}

void f(){
    using namespace t;
    print();
}

int main(int argc, char *argv[])
{
    f();
    return 0;
}
