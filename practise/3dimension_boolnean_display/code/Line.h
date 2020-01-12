#ifndef LINE_BOOLEAN
#define LINE_BOOLEAN

#include"Direction.h"
#include"Point.h"
#include"Tol.h"
#include<iostream>

class Line{
protected:
    Point fixpoint;
    Direction direct;
public:
    Line(){}
    Line(const Point& p, const Direction& d) : fixpoint(p), direct(d.unit()) {}
    Line(const Point& p1, const Point& p2) : fixpoint(p1), direct((p2 - p1).unit()){}
    Line(const Line& l) : fixpoint(l.fixpoint), direct(l.direct) {}
    Line& operator=(const Line& l) {
        fixpoint = l.fixpoint;
        direct = l.direct;
        return *this;
    }
    ~Line(){}
    Point getfixpoint() const {
        return fixpoint;
    }
    void setfixpoint(const Point& p){
        fixpoint = p;
    }
    Direction getdirect() const {
        return direct;
    }
    void setdirect(const Direction& d) {
        if(d.norm() > (1 + Tol::t) || d.norm() < (1 - Tol::t)){
            std::cout << "set wrong Line::direct .";
            int i;
            std::cin >> i;
        }
        direct = d;
    }
    bool ifcontainPoint(const Point&) const;
    bool ifintersectionLine(const Line& l2) const;
    Point intersectionLine(const Line& l2) const;
    bool ifoverlapLine(const Line& l) const;
};

#endif