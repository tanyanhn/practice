#include"Flat.h"
#include"Point.h"
#include"Direction.h"
#include"Line.h"
#include"Det.h"
#include"Data.h"
#include"Segment.h"
#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

bool Flat::ifintersectionLine(const Line& l) const {
    Direction d1 = normaldirect, d2 = l.getdirect();
    double d = fabs(d1.dot(d2));
    return d > Tol::t;
}

Point Flat::intersectionLine(const Line& l) const {
    Det det;
    if(!ifintersectionLine(l)){
        cout << "Flat::intersectionLine: " << endl;
        int i;
        cin >> i;
    }
    Direction d1 = normaldirect, d2 = l.getdirect();
    Point p1 = fixpoint, p2 = l.getfixpoint();
    double a00 = d1[0], a01 = d1[1], a02 = d1[2], a03 = d1[0] * p1[0] + d1[1] * p1[1] + d1[2] * p1[2],
        a10 = d2[1], a11 = -d2[0], a12 = 0, a13 = d2[1] * p2[0] - d2[0] * p2[1],
        a20 = d2[2], a21 = 0, a22 = -d2[0], a23 = d2[2] * p2[0] - d2[0] * p2[2];
    double x, y, z;
    double m = det(a00, a01, a02,
                   a10, a11, a12,
                   a20, a21, a22);
    x = det(a03, a01, a02,
            a13, a11, a12,
            a23, a21, a22) / m;
    y = det(a00, a03, a02,
            a10, a13, a12,
            a20, a23, a22) / m;
    z = det(a00, a01, a03,
            a10, a11, a13,
            a20, a21, a23) / m;
    return Point(x, y, z);
}


bool Flat::ifintersectionFlat(const Flat& f1) const {
    Direction d1 = normaldirect, d2 = f1.getnormaldirect();
    if(d1.cross(d2).norm() < Tol::t)
        return false;
    return true;
}


Line Flat::intersectionFlat(const Flat& f1) const {
    Det det;
    Direction linedirect = normaldirect.cross(f1.normaldirect).unit();
    int i;
    if(fabs(linedirect[0]) > fabs(linedirect[1]))
        if(fabs(linedirect[0]) > fabs(linedirect[2]))
            i = 0;
        else
            i = 2;
    else
        if(fabs(linedirect[1]) > fabs(linedirect[2]))
            i = 1;
        else
            i = 2;
    Direction d1 = normaldirect, d2 = f1.getnormaldirect();
    Point p1 = fixpoint, p2 = f1.getfixpoint();
    double a00 = d1[0], a01 = d1[1], a02 = d1[2], a03 = d1[0] * p1[0] + d1[1] * p1[1] + d1[2] * p1[2],
        a10 = d2[0], a11 = d2[1], a12 = d2[2], a13 = d2[0] * p2[0] + d2[1] * p2[1] + d2[2] * p2[2],
        a20 = 0, a21 = 0, a22 = 0, a23 = 1;
    if(i == 0){
        a20 = 1;
    }
    if(i == 1){
        a21 = 1;
    }
    if(i == 2){
        a22 = 1;
    }
    double x, y, z;
    double m = det(a00, a01, a02,
                   a10, a11, a12,
                   a20, a21, a22);
    x = det(a03, a01, a02,
            a13, a11, a12,
            a23, a21, a22) / m;
    y = det(a00, a03, a02,
            a10, a13, a12,
            a20, a23, a22) / m;
    z = det(a00, a01, a03,
            a10, a11, a13,
            a20, a21, a23) / m;
    return Line(Point(x, y, z), linedirect);
}

bool Flat::ifcontainPoint(const Point& p) const {
    Direction d = p - fixpoint;
    double f = fabs(d.dot(normaldirect));
    return f < Tol::t;
}

bool Flat::ifcontainSegment(const Segment& seg) const {
    if(ifcontainPoint(Data::points[seg[0]]) && ifcontainPoint(Data::points[seg[1]]))
        return true;
    return false;
}

double Flat::angleBetweenFlats(const Flat& pl2,const Direction& di) const {
    Direction d1 = Flat::normaldirect,
        d2 = pl2.getnormaldirect();
    if(d1.cross(d2).dot(di) < -Tol::t)
        return M_PI + acoss(d2.dot(d1));
    else if(d1.cross(d2).dot(di) > Tol::t)
        return M_PI - acos(d2.dot(d1));
    else if(d1.dot(d2) < 0)
        return 0;
    else if(d1.dot(d2) > 0)
        return M_PI;
}