#include "Dependency2.h"
using namespace std;

int separator() {
    cout << "--------------------" << endl;
    return 1;
}

extern Dependency1 dep1;
Dependency2 dep2(dep1);
Dependency1 dep1;
int x1 = separator();

Dependency1 dep1b;
Dependency2 dep2b(dep1b);
int x2 = separator();

Dependency1& d1 () {
    static Dependency1 dep1;
    return dep1;
}

Dependency2& d2() {
    static Dependency2 dep2(d1());
    return dep2;
}

int main() {
    Dependency2& dep2 = d2();
}
