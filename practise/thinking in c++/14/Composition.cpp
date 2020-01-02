// Reuse code with composition
#include "Useful.h"

class Y {
    int i;
public:
    X x; // Embedded object
    Y(){ i = 0; }
    ~Y(){}
    void f(int ii) { i = ii; }
    int g() const {return i; }
    void print(){}
};

int main() {
    Y y;
    y.f(47);
    y.x.set(37); // Access the embedded object
}
