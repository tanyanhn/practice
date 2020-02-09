#include"Segment.h"
#include<cmath>
//#include"Point.h"
//#include"Line.h"
using namespace std;


bool Segment::ifcontainPoint(const Point& p) const {
    Point p0 = Data::points[points[0]],
        p1 = Data::points[points[1]];
    if((p == p0) || (p == p1))
        return true;
    if(!Line::ifcontainPoint(p))
        return false;
    Direction direct1 = (p - Data::points[points[0]]),
        direct2 = Data::points[points[1]] - Data::points[points[0]];
    double d1 = direct1.dot(direct2),
        d2 = (direct2.norm()) * (direct2.norm());
    if(d1 < 0 || d1 > d2)
        return false;
    return true;
}


bool Segment::ifintersectionSegment(const Segment& seg2) const {
    if(!ifintersectionLine(seg2))
        return false;
    Point p(intersectionLine(seg2));
    if(!(p > Data::points[points[0]] && p < Data::points[points[1]] &&
         p > Data::points[seg2[0]] && p < Data::points[seg2[1]]))
        return false;
    return true;
}

Point Segment::intersectionSegment(const Segment& seg2) const {
    if(!ifintersectionSegment(seg2)){
        std::cout << "Segment don't intersect :" << id << " : " << seg2.id;
        int* i = 0;
        cout << *i;
    }
    return Point(intersectionLine(seg2));
}

bool Segment::ifoverlapSegment(const Segment& seg2) const {
    //  if((direct.unit() - seg2.getdirect().unit).norm() > Tol::t)
    //  return false;
    Point p10 = Data::points[points[0]], p11 = Data::points[points[1]],
        p20 = Data::points[seg2[0]], p21 = Data::points[seg2[1]];
    if((p11 < p20) || (p21 < p10))
        return false;
    if(p21 < p11){
        if(ifcontainPoint(p21) == false)
            return false;
    }
    else{
        if(seg2.ifcontainPoint(p11) == false)
            return false;
    }
    if(p20 < p10){
        if(seg2.ifcontainPoint(p10) == false)
            return false;
    }
    else{
        if(ifcontainPoint(p20) == false)
            return false;
    }
    return true;
}

Segment Segment::overlapSegment(const Segment& seg2) const {
    if(ifoverlapSegment(seg2) == false){
        cout << "Segment::overlapSegment wrong : " << id <<
            " : " << seg2.getid() ;
        int* i = 0;
        cout << *i;
    }
    Point p10 = Data::points[points[0]], p11 = Data::points[points[1]],
        p20 = Data::points[seg2[0]], p21 = Data::points[seg2[1]],
        p0 , p1;
    if(p21 < p11){
        p1 = p21;
    }
    else{
        p1 = p11;
    }
    if(p20 < p10){
        p0 = p10;
    }
    else{
        p0 = p20;
    }
    return Segment(p0.getid(), p1.getid());
}

bool Segment::operator<(const Segment& seg2) const {
    Point p1 = Tol::l->intersectionLine(*this),
                       p2 = Tol::l->intersectionLine(seg2);
    if(p1 == p2){
        Direction d1, d2, d = Tol::l->getdirect();
        if(p1.getid() == (*this)[0]){
            d1 = Data::points[(*this)[1]] - Data::points[(*this)[0]];
        }
        else{
            d1 = Data::points[(*this)[0]] - Data::points[(*this)[1]];
        }
        if(p2.getid() == seg2[0]){
            d2 = Data::points[seg2[1]] - Data::points[seg2[0]];
        }
        else{
            d2 = Data::points[seg2[0]] - Data::points[seg2[1]];
        }
        return d.angle(d1, *Tol::outside) < d.angle(d2, *Tol::outside);
    }
    return p1 < p2;
}