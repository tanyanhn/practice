#include <iostream>
#include <vector>
#include "../require.h"
using namespace std;

class Rodent {
public:
    virtual void f() { cout << "Rodent::f()\n";}
    virtual ~Rodent() = 0;//{ cout << "~Rodent()\n";}
};
inline Rodent::~Rodent() { cout << "~Rodent()\n";}
class Mouse : public Rodent {
public:
    void f() { cout << "Mouse::f()\n";}
};

class Gerbil : public Rodent {
public:
    void f() { cout << "Gerbil::f()\n";}
};

class Hamster : public Rodent {
public:
    void f() { cout << "Hamster::f()\n";}
    ~Hamster() { cout << "~Hamster()\n";}
};

class BlueHamster : public Hamster {
public:
    void f() { cout << "BlueHamster::f()\n";
        Rodent::f();}
};


int main(int argc, char *argv[])
{
    Mouse m; Gerbil g; Hamster h;
    m.f(); g.f(); h.f();
    vector<Rodent*> v;
    v.push_back(&m);v.push_back(&g);v.push_back(&h);
    BlueHamster b;v.push_back(&b);
    b.f();
    Rodent* rp = new Hamster;
    delete rp;
    cout << endl;
    return 0;
}
