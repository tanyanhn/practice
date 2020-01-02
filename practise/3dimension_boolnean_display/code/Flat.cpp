#include"Flat.h"
#include"Point.h"
#include"Direction.h"
#include"Line.h"

Line Flat::intersectionFlat(const Flat& f1) const {
    Direction direct = normaldirect.cross(f1.normaldirect).unit();
    double x, y, z;
    if(direct[0] > Tol::t)
}