#include"Planar.h"
#include"Line.h"
#include<iostream>
#include<math.h>
using namespace std;


Planar::Planar(std::vector<int> p, std::vector<int> s, int identity , int inF , int inY )
    : Flat(Data::points[p[0]], Data::points[p[1]], Data::points[p[2]]),
      points(p), segments(s), id(identity), inFace(inF), inYinset(inY) {
    /*
    for(auto i = points.begin(); i != points.end(); i++){
        existpoints.insert(*i);
    }
    */
    for(auto i = segments.begin(); i != segments.end(); i++){
        existsegments.insert(*i);
    }
}

Planar::Planar(const Planar& pl) :
    Flat(pl),
    points(pl.points), segments(pl.segments),
    existpoints(pl.existpoints), existsegments(pl.existsegments),
    id(pl.id), inFace(pl.inFace), inYinset(pl.inYinset) {}



bool Planar::ifcontainPoint(const Point& p) const {
    if(Flat::ifcontainPoint(p) == false)
        return false;
    Point p0 = Data::points[points[0]],
        p1 = Data::points[points[1]],
        p2 = Data::points[points[2]];
    Segment seg0 = Data::segments[segments[0]],
        seg1 = Data::segments[segments[1]],
        seg2 = Data::segments[segments[2]];
    if((p == p0) ||
       (p == p1) ||
       (p == p2))
        return true;
    if(seg0.ifcontainPoint(p) ||
       seg1.ifcontainPoint(p) ||
       seg2.ifcontainPoint(p))
        return true;
    Direction d0 = p - p0, d1 = p - p1, d2 = p - p2;
    Direction d01 = p1 - p0, d12 = p2 - p1, d20 = p0 - p2;
    if((d0.cross(d01).dot(normaldirect) < 0) ||
       (d1.cross(d12).dot(normaldirect) < 0) ||
       (d2.cross(d20).dot(normaldirect) < 0))
        return false;
    return true;
}


bool Planar::ifcontainSegment(const Segment& seg) const {
    Point p0 = Data::points[seg[0]], p1 = Data::points[seg[1]];
    bool ifp0,ifp1;
    ifp0 = ifcontainPoint(p0);
    ifp1 = ifcontainPoint(p1);
    if(ifp0 && ifp1)
        return true;
    return false;
}

bool Planar::ifcontainPlanar(const Planar& pl2) const {
    Point p0 = Data::points[(pl2.getpoints()).[0]],
        p1 = Data::points[(pl2.getpoints()).[1]],
        p2 = Data::points[(pl2.getpoints()).[2]];
    return ifcontainPoint(p0) && ifcontainPoint(p1) && ifcontainPoint(p2);
}


bool Planar::ifintersectionSegment(const Segment& seg) const {
    Point p0 = Data::points[seg[0]], p1 = Data::points[seg[1]],
        plp0 = Data::points[points[0]], plp1 = Data::points[points[1]],
        plp2 = Data::points[points[2]];
//    Segment seg0 = Data::segments[segments[0]],
//        seg1 = Data::segments[segments[1]],
//        seg2 = Data::segments[segments[2]];
    if(Flat::ifintersectionLine(seg) == false)
        return false;
    Point p(Flat::intersectionLine(seg));
    if(!(p == p0) && !(p == p1) && (seg.ifcontainPoint(p) == false))
        return false;
    if(/*(seg0.ifcontainPoint(p) == false) &&
       (seg1.ifcontainPoint(p) == false) &&
       (seg2.ifcontainPoint(p) == false) &&
       (p != plp0) && (p != plp1) && (p != plp2) &&*/
       (ifcontainPoint(p) == false))
        return false;
    return true;
}


Point Planar::intersectionSegment(const Segment& seg) const {
    if(ifintersectionSegment(seg) == false){
        std::cout << "Planar intersectionSegment wrong :" << id <<
            " :" << seg.getid() << std::endl;
        int i;
        cin >> i;
    }
    Point p(Flat::intersectionLine(seg));
    return p;
}

/*
double Planar::angleBetweenPlanars(const Planar& pl2,const Direction& di) const {
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
*/

/*
  Planar Planar::intersectionPlanar(const Planar& pl) const {
  Segment seg0 = Data::segments[pl.getsegments().[0]],
  seg1 = Data::segments[pl.getsegments().[1]],
  seg2 = Data::segments[pl.getsegments().[2]];
  Point p0 = intersectionLine(seg0),
  p1 = intersectionLine(seg1),
  p2 = intersectionLine(seg2);
  if((ifcontainPoint(p0) == true) ||
  (ifcontainPoint(p1) == true) ||
  (ifcontainPoint(p2) == true))
  return true;
  p0.setid(Data::pointsnum);
  Data::points[Data::pointsnum] = p0;
  Data::pointsnum++;
  p1.setid(Data::pointsnum);
  Data::points[Data::pointsnum] = p1;
  Data::pointsnum++;
  p2.setid(Data::pointsnum);
  Data::points[Data::pointsnum] = p2;
  Data::pointsnum++;
  Segment seg
  }


  bool Planar::ifintersectionFlat(const Planar& pl) const {
    if(Flat::ifintersectionFlat(pl) == false){
        return false;
    }
    Line l(Flat::intersectionFlat(pl));
}*/

