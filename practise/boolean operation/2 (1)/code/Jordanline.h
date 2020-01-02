#ifndef JORDANLINE
#define JORDANLINE


#include"Sweepline.h"
#include"Spajor.h"
#include<vector>
#include<iostream>
using namespace std;

class Spajor;
class Sweepline;

class Jordanline  {
    vector<int> line;
    int identity;
    int leftjordanline;
    int type;
public:
    explicit Jordanline(const vector<int>& vi, const int ident = -2) : line(vi), identity(ident), leftjordanline(-2), type(-2) {}
    Jordanline(const Jordanline& jl) : line(jl.line), identity(jl.identity), leftjordanline(jl.leftjordanline), type(jl.type) {}
    Jordanline& operator=(const Jordanline& jl){
        line = jl.line;
        identity = jl.identity;
        leftjordanline = jl.leftjordanline;
        type = jl.type;
        return *this;
    }
    ~Jordanline(){}
    const int& operator[](const int i) const {
        if(i < 0 || i > line.size() - 1) {
            cout << "jordanline[] out of range wrong";
            exit(0);
        }
        return line[i];
    }
    int& operator[](const int i){
        if(i < 0 || i > line.size() - 1) {
            cout << "jordanline[] out of range wrong";
            exit(0);
        }
        return line[i];
    }
    void setline(vector<int> vi){
        line.erase(line.begin(), line.end());
        line = vi;
    }
    const int size() const {
        return line.size();
    }
    const int getidentity() const {
        return identity;
    }
    void setidentity(const int i){
        identity = i;
    }
    const int getleftjordanline() const {
        return leftjordanline;
    }
    void setleftjordanline(const int i){
        leftjordanline = i;
    }
    void setinspajor(const int j);
    const int gettype() const {
        return type;
    }
    void settype(const int i){
        type = i;
    }
    void update();
    static const Spajor generator() ;
    friend ostream& operator<<(ostream& os, const Jordanline& jl);
};

#endif