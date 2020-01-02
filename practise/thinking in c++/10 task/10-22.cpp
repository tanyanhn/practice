#include "10-22.1.h"
#include "10-22.2.h"

#include <iostream>

#include "../require.h"
using namespace std;
//using namespace A;
//using namespace B;

void f(){
    //using namespace A;
    //using namespace B;
    using A::myclass;
    myclass my1;
    B::myclass my2;
    my1.print();
    my2.print();
}
int main(int argc, char *argv[])
{
    f();
    return 0;
}
