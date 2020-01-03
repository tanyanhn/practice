#include"Flat.h"
#include"Point.h"
#include"Direction.h"
#include"Line.h"
#include"Det.h"
using namespace std;

bool Flat::ifintersectionLine(const Line& l) const {
    Direction d1 = normaldirect, d2 = l.getdirect();
    double d = d1.dot(d2);
    return d > Tol::t
}

Point Flat::intersectionLine(const Line& l) const {
    if(!ifintersectionLine(l)){
        cout << "Flat::intersectionLine: " << endl;
        exit(0);
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


Line Flat::intersectionFlat(const Flat& f1) const {
    Direction direct = normaldirect.cross(f1.normaldirect).unit();
    double x, y, z;
    if(direct[0] > Tol::t)
}