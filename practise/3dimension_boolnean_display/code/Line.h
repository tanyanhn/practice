#ifndef LINE_BOOLEAN
#define LINE_BOOLEAN

#include"Direction.h"
#include"Point.h"

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
    }
    ~Line(){}
    Direction getdirect() const {
        return direct;
    }
    bool ifcontainPoint(const Point&) const;
    bool ifintersectionLine(const Line& l2) const;
    Point intersectionLine(const Line& l2) const;
};

#endif