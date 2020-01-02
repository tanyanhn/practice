#ifndef SPAJOR
#define SPAJOR

#include"Sweepline.h"
#include"HassNode.h"
#include"Point.h"
#include<iostream>
using namespace std;

class Point;

class Spajor{
    vector<HassNode> hassmap;
    vector<int> jordanline;
    bool type;
    int identity;
public:
    Spajor(vector<HassNode> hass, vector<int> jl, bool b, int i) : hassmap(hass), jordanline(jl), type(b), identity(i){}
    Spajor(const Spajor& s) : hassmap(s.hassmap), jordanline(s.jordanline), type(s.type), identity(s.identity){}
    Spajor& operator=(const Spajor& s){
        hassmap = s.hassmap;
        jordanline = s.jordanline;
        type = s.type;
        identity = s.identity;
        return *this;
    }
    const vector<HassNode> gethassmap(){
        return hassmap;
    }
    const int size() const {
        return jordanline.size();
    }
    const int operator[](const int i) const {
        if(i < 0 || i > size() - 1) cout << "Spajor [] wrong";
        return jordanline[i];
    }
    int& operator[](const int i) {
        if(i < 0 || i > size() - 1) cout << "Spajor [] wrong";
        return jordanline[i];
    }
    void setjordanline(vector<int> vi){
        jordanline = vi;
    }
    const bool gettype() const {
        return type;
    }
    void settype(const bool i){
        type = i;
    }
    const int getidentity() const {
        return identity;
    }
    void setidentity(const int i){
        identity = i;
    }
    const Spajor complement() const;
    const Spajor meet(const Spajor&) const;
    const Spajor join(const Spajor&) const;
    const int IfInSpajor(const Point& ) const;
    friend ostream& operator<<(ostream& os, const Spajor&);
};

#endif