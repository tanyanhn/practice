#ifndef TRIANGLEINTERSECTION_BOOLEAN
#define TRIANGLEINTERSECTION_BOOLEAN

#include"Segment.h"
#include"Planar.h"

class TriangleIntersection {
public:
    Segment PlanarIntersectLine(const Planar&, const Line& l,
                                bool&, bool&, bool&);
    void operator()(Planar&, Planar&);
};


#endif