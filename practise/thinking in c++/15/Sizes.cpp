// Object sizes with/without virtual functions
#include <iostream>
using namespace std;

class NoVirtual  {
    int a;
public:
    void x() const {}
    int i() const { return 1; }
    NoVirtual(){}
    ~NoVirtual(){}
    void print(){}
};

class OneVirtual {
     int a;
public:
    virtual void x() const {}
    int i() const { return 1; }
};

class TwoVirtuals  {
    int a;
public:
    virtual void x() const {}
    virtual int i() const { return 1; }
    TwoVirtuals(){}
    ~TwoVirtuals(){}
    void print(){}
};
int main() {
    cout << "int: " << sizeof(int) << "\n";
    cout << "NoVirtual: " << sizeof(NoVirtual) << "\n";
    cout << "void* : " << sizeof(void*) << "\n";
    cout << "OneVirtual: " << sizeof(OneVirtual) << "\n";
    cout << "TwoVirtuals: " << sizeof(TwoVirtuals) << "\n";
}
