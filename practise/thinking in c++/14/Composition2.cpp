// Private embedded objects
#include "Useful.h"
class Y{
    int i;
    X x; // Embedded object
public:
    Y(){ i = 0; }
    ~Y(){}
    void f(int ii) { i = ii; x.set(ii); }
    int g() const { return i * x.read(); }
    void permute() { x.permute(); }
    void print(){}
};

int main() {
    Y y;
    y.f(47);
    y.permute();
}
