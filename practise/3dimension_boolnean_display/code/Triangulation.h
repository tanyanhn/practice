#ifndef TRIANULATION_BOOLEAN
#define TRIANULATION_BOOLEAN

#include<set>
#include<map>
#include"Point.h"
#include"Segment.h"
#include"Planar.h"
using std::map;
using std::set;
using std::vector;

class Segment;

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
    vector<Planar> generatorPolygen();
    vector<Planar> TriangulateMonotonePolygon(Planar&);
public:
    std::vector<Planar> operator()(Planar&);
};

#endif