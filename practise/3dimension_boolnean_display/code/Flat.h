#ifndef FLAT_BOOLEAN
#define FLAT_BOOLEAN

#include"Point.h"
#include"Direction.h"
#include"Tol.h"
//#include"Segment.h"
#include<math.h>
#include<iostream>

class Line;
class Point;
class Segment;
class Data;
class Flat{
protected:
    Point fixpoint;
    Direction normaldirect;
public:
    Flat(){}
    Flat(const Point& p, const Direction& nd) : fixpoint(p), normaldirect(nd.unit()) {}
    Flat(const Point& p, const Direction& d1, const Direction d2) : fixpoint(p) ,normaldirect(d1.cross(d2).unit()) {}
    Flat(const Point& p1, const Point& p2, const Point p3) {
        Direction d1 = p2 - p1;
        Direction d2 = p3 - p1;
        normaldirect = d1.cross(d2).unit();
        fixpoint = p1;
    }
    Flat(const Flat& f) //: fixpoint(f.fixpoint), normaldirect(f.normaldirect)
        {
            *this = f;
        }
    Flat& operator=(const Flat& f) {
        fixpoint = f.fixpoint;
        normaldirect = f.normaldirect;
        return *this;
    }
    ~Flat(){}
    Point getfixpoint() const {
        return fixpoint;
    }
    void setfixpoint(const Point& p) {
        fixpoint = p;
    }
    Direction getnormaldirect() const {
        return normaldirect;
    }
    void setnormaldirect(const Direction& d) {
        if(d.norm() < (1 - Tol::t) || d.norm() > (1 + Tol::t)){
            std::cout << "Flat::setnormaldirect not unit.";
            int* pi = 0;
            cout << *pi;
        }
        normaldirect = d;
    }
    bool ifintersectionFlat(const Flat& f1) const;/* {
        if(normaldirect.unit().cross(f1.normaldirect.unit()).norm() < Tol::t)
            return false;
        return true;
        }*/
    bool ifintersectionLine(const Line& l1) const;/* {
        if(normaldirect.unit().dot(l1.getdirect().unit()) < Tol::t)
            return false;
        return true;
        }*/
    Line intersectionFlat(const Flat& f1) const;
    Point intersectionLine(const Line& l1) const;
    bool ifcontainPoint(const Point& p) const;
    bool ifcontainSegment(const Segment& seg) const;
    double angleBetweenFlats(const Flat&, const Direction&) const;
};

#endif
