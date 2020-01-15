#ifndef FUNCTOR_BOOLEAN
#define FUNCTOR_BOOLEAN

#include"Data.h"
#include"Planar.h"
#include"Face.h"
#include"Segment.h"
#include"Yinset.h"
#include<vector>
#include<set>


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
    set<Segment> sweepflat;
    map<int, int> helper;
    Planar pl;
    void makeMonotone();
    void handleStartVertex(Point&);
    void handleEndVertex(Point&);
    void handleSplitVertex(Point&);
    void handleMergeVertex(Point&);
    void handleRegularVertex(Point&);
    vector<Planar> generatorYMonotone();
    vector<Planar> TriangulateMonotonePolygon(Planar&);
public:
    std::vector<Planar> operator()(Planar&);
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