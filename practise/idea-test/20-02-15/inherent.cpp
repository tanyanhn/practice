#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class A {
public:
    A(){
        cout << "A()" << endl;
    }
    virtual ~A(){};
};

class B{
public:
    B(){
        cout << "B()" << endl;
    }
    virtual ~B(){};
};

class C : public A, public B{
    vector<int> v;
public:
    C() : v(5,1) {
        cout << "C()" << endl;
    }
    vector<int> getvector(){
        return v;
    }
    //virtual ~C();
};

int main(){
    A* pa = new A,
        * paa;
    B* pb = new B,
        * pbb;
    C* pc = new C,
        * pcc;
    A& ra = *pc;
    paa = pc;
    //pcc = static_cast<C*>(pa);
    pbb = dynamic_cast<B*>(paa);
    pbb = dynamic_cast<B*>(&ra);
    vector<int> v = pc->getvector();
    //v[7] = 0;
    for_each(v.begin(), v.end(), [](auto i){
            cout << i << endl;
        });
    delete pa, pb, pbb;
}