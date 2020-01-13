#ifndef FUNCTOR_BOOLEAN
#define FUNCTOR_BOOLEAN

#include"Data.h"
#include"Planar.h"
#include"Face.h"
#include"Segment.h"
#include"Yinset.h"
#include<vector>


class TriangleIntersection {
public:
    Segment PlanarIntersectLine(const Planar&, const Line& l,
                                bool&, bool&, bool&);
    void operator()(Planar&, Planar&);
};

class SegmentIntersection {
public:
    void operator()(Planar&);
}

class Triangulation {
public:
    std::vector<Planar> operator()(const Planar&);
};

class YinsetContainTriangle {
    enum{AddOverlap = 0, notAddOverlap = 1}
    bool operator()(const Yinset& , const Planar&, int);
};

class FindNearTriangle {
    std::vector<Planar> operator()(const Planar&);
};

class FaceContainFace {
    bool operator()(const Face&, const Face&);
};

#endif