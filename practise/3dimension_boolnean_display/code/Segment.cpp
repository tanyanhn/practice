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