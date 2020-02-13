#include<iostream>
using namespace std;


class Grandfather{
public:
    virtual void fun() = 0;
};

void Grandfather::fun(){
    cout << "Grandfather" << endl;
}

class father : public Grandfather{
public:
    void fun(){
        Grandfather::fun();
        cout << "father" << endl;
    }
};

class people : public father{
public:
    void fun(){
        cout << "people" << endl;
    }
};


int main(){
    people p;
    father f;
    //Grandfather g;
    Grandfather& rp = p,
        & rf = f;
        //  &rg = g;
    rp.fun();
    rf.fun();
    //rg.fun();
    father* pp = &p,
        * pf = &f;
        //&rg = g;
    pp->fun();
    pf->fun();
    //rg.fun();
}