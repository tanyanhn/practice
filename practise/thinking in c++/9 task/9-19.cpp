#include <string>
#include <iostream>
#include "../require.h"
using namespace std;

#define FIELD(type, name)                       \
    private:                                    \
    type name ## _;                             \
public:                                         \
type name() const {return name ##_;}            \
void name(type val) {name ## _ = val;}

class C {
    FIELD(int, foo);
    FIELD(float, bar);
    FIELD(string, baz);
};

int main(int argc, char *argv[])
{
    C c;
    c.foo(1);
    c.bar(2.1);
    c.baz("three");
    cout << c.foo() << endl;
    cout << c.bar() << endl;
    cout << c.baz() << endl;
    return 0;
}
