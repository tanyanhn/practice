#include"Segment.h"
//#include"Point.h"
//#include"Line.h"


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
        int i;
        std::cin >> i;
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
        int i;
        cin >> i;
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

