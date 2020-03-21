#include"Point.h"
#include"Tol.h"
#include"Segment.h"

void Point::print() const{
    cout << "(" << coord[0] << "," << coord[1] << "," << coord[2] << ")";
}

void Point::setid(const int i) {
    for(auto j = inSegment.begin(); j != inSegment.end(); j++){
        Segment seg = Data::segments[*j];
        if(seg[0] == id){
            Data::segments[*j].setendpoints(0, i);
        }
        else if(seg[1] == id){
            Data::segments[*j].setendpoints(1, i);
        }
        else {
            cout << "Point::setid() wrong :" << id;
            int* pi = 0;
            cout << *pi;
        }
    }
    id = i;
    if(id != -1){
        if(id >= Data::points.size())
            Data::points.resize(id + 1);
        Data::points[id] = *this;
    }
}


Point::Point(const double x, const double y, const double z, const int identity, const set<int> &v, const int it) : coord{x, y, z}, id(identity), inSegment(v), inYinset(it) {/*
    coord[0] = x;
    coord[1] = y;
    coord[2] = z;
    id = identity;
    insegment = v;
    intriangle = it;*/
    if(id != -1){
        if(id >= Data::points.size())
            Data::points.resize(1 + id);
        Data::points[id] = *this;
    }
}

Point::Point(const Point& q){
    /*
    coord[0] = q.coord[0];
    coord[1] = q.coord[1];
    coord[2] = q.coord[2];
    id = q.id;
    inSegment = q.inSegment;
    inYinset = q.inYinset;
    */
    *this = q;
}

Point& Point::operator=(const Point& q){
    coord[0] = q.coord[0];
    coord[1] = q.coord[1];
    coord[2] = q.coord[2];
    id = q.id;
    inSegment = q.inSegment;
    inYinset = q.inYinset;
    return *this;
}


bool Point::operator<(const Point& q) const {
    if(coord[2] < q.coord[2] - Tol::t)
        return true;
    else if((coord[2] < q.coord[2] + Tol::t) &&
            (coord[1] < q.coord[1] - Tol::t))
        return true;
    else if((coord[2] < q.coord[2] + Tol::t) &&
            (coord[1] < q.coord[1] + Tol::t) &&
            (coord[0] < q.coord[0] - Tol::t))
        return true;
    else
        return false;
}


ostream& operator<<(ostream& os, const Point& p){
    return os << p[0] << " "
              << p[1] << " "
              << p[2] << " ";
}

istream& operator>>(istream& is, Point& p){
    double d0, d1, d2;
    is >> d0 >> d1 >> d2;
    p[0] = d0;
    p[1] = d1;
    p[2] = d2;
    return is;
}