#include"Line.h"
#include"Tol.h"
#include"Flat.h"
#include"Direction.h"
#include"Point.h"
#include<math.h>
#include<iostream>
using namespace std;

bool Line::ifintersectionLine(const Line& l2) const {
    Direction d0 = fixpoint - l2.getfixpoint(),
        d1 = direct,
        d2 = l2.getdirect();
    if(Point() + d1 < Point()){
        d1 = d1 * (-1);
    }
    if(Point() + d2 < Point()){
        d2 = d2 * (-1);
    }
    if((d1.unit() - d2.unit()).norm() < Tol::t)
        return false;
    if(fabs(d1.cross(d2).unit().dot(d0)) < Tol::t)
        return true;
    else return false;
}

Point Line::intersectionLine(const Line& l2) const {
    if(ifintersectionLine(l2) == false){
        cout << "Line did't intersection \n";
        int* pi = 0;
        cout << *pi;
        //exit(0);
    }
    Direction d0 = direct.cross(l2.getdirect());
    Direction normaldirect = d0.cross(direct).unit();
    Flat f(fixpoint, normaldirect);
    return f.intersectionLine(l2);
    // double x, y, z;
    //Direction2D p1(l1.getfixpoint().[0], l1.getfixpoint().[1], 0),
    //    p2(l2.getfixpoint().[0], l2.getfixpoint().[1], 0);
}

bool Line::ifcontainPoint(const Point& p) const {
    Point p1(fixpoint), p2(fixpoint + direct);
    double d = ((p - p1).cross(p1 - p2).norm()) / ((p1 - p2).norm());
    if(d < Tol::t)
        return true;
    else
        return false;
}

bool Line::ifoverlapLine(const Line& l) const {
    if(ifcontainPoint(l.getfixpoint()) == false)
        return false;
    if(fabs(direct.cross(l.getdirect()).norm()) > Tol::t)
        return false;
    return true;
}