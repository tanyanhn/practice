#include"Point.h"
#include"Tol.h"


Point::Point(const double x, const double y, const double z, const int identity, const vector<int> &v, const int it) : coord{x, y, z}, id(identity), inSegment(v), inYinset(it) {/*
    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
    id = identity;
    insegment = v;
    intriangle = it;*/
}

Point::Point(const Point& q){
    coord[0] = q.coord[0];
    coord[1] = q.coord[1];
    coord[2] = q.coord[2];
    id = q.id;
    inSegment = q.inSegment;
    inYinset = q.inYinset;
}

Point& Point::operator=(const Point& q){
    coord[0] = q.coord[0];
    coord[1] = q.coord[1];
    coord[2] = q.coord[2];
    id = q.id;
    inSegment = q.inSegment;
    inYinset = q.inYinset;
}


bool Point::operator<(const Point& q) const {
    if(coord[2] < q.coord[2] - Tol::t)
        return true;
    else if((coord[2] < q.coord[2] + Tol::t)
            && (coord[1] < q.coord[1] - Tol::t))
        return true;
    else if((coord[2] < q.coord[2] + Tol::t) &&
            (coord[1] < q.coord[1] + Tol::t) &&
            (coord[0] < q.coord[0] - Tol::t))
        return true;
    else
        return false;
}