#include <iostream>

#include "../require.h"
using namespace std;

class Trace {
    int n;
public:
    Trace(int n){
        cout << "Trace::Trace(" << n <<")\n";
        this->n = n;
    }
    Trace(const Trace& t ){
        cout << "Trace::Trace(const Trace&)\n";
        n = t.n;
    }
    int getN() const {
        return n;
    }
    ~Trace(){
        cout << "~Trace()\n";
    }
    void print(){
        cout << n << endl;
    }
};

void f(Trace t) {
    cout << "f(" << t.getN() << ")\n";
}

Trace g() {
    Trace t(2);
    return t;
}

Trace h(int n) {
    return n;
}

int main(int argc, char *argv[])
{
    Trace t1 = 1;
    f(t1);
    Trace t2 = g();
    t2.print();
    Trace t3 = h(3);
    return 0;
}
