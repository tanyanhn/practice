#ifndef FUNCTOR_BOOLEAN
#define FUNCTOR_BOOLEAN

#include"Data.h"
#include"Planar.h"
#include"Face.h"
#include"Segment.h"
#include"Yinset.h"
#include<vector>
#include<set>
#include<map>
using std::vector;
using std::set;
using std::map;

class TriangleIntersection {
public:
    Segment PlanarIntersectLine(const Planar&, const Line& l,
                                bool&, bool&, bool&);
    void operator()(Planar&, Planar&);
};

class SegmentIntersection {
public:
    void operator()(Planar&);
};

class Triangulation {
    //private:
    set<Segment> sweepflat;
    map<int, set<Segment>::iterator> sweepflatposition;
    enum PointType {start = 0, end = 1, split = 2, merge = 3, regular = 4};
    map<int, pair<PointType, int>> helper;
    Planar pl;
    void makeMonotone();
    void handleStartVertex(Point&, set<Segment>::iterator& ei);
    void handleEndVertex(Point&, set<Segment>::iterator& ei);
    void handleSplitVertex(Point&, set<Segment>::iterator& ei, set<Segment>::iterator& ej);
    void handleMergeVertex(Point&, set<Segment>::iterator& ei, set<Segment>::iterator& ej);
    void handleRegularLeftVertex(Point&, set<Segment>::iterator& ei1,
                                 set<Segment>::iterator& ei2);
    void handleRegularRightVertex(Point&, set<Segment>::iterator& ej);
    vector<Planar> generatorYMonotone();
    vector<Planar> TriangulateMonotonePolygon(Planar&);
public:
    std::vector<Planar> operator()(Planar&);
};

class YinsetContainTriangle {
    enum{AddOverlap = 0, notAddOverlap = 1};
    bool operator()(const Yinset& , const Planar&, int);
};

class FindNearTriangle {
    std::vector<Planar> operator()(const Planar&);
};

class FaceContainFace {
    bool operator()(const Face&, const Face&);
};

#endif