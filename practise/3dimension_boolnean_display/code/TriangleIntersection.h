#ifndef TRIANGLEINTERSECTION_BOOLEAN
#define TRIANGLEINTERSECTION_BOOLEAN

#include"Segment.h"
#include"Planar.h"

class TriangleIntersection {
public:
    Segment PlanarIntersectLine(const Planar&, const Line& l,
                                bool&, bool&, bool&);
    bool IdentityEdge(Segment&, Segment&);
    void operator()(Planar&, Planar&);
};

class PastEdge{
    set<int> inPlanar1;
    int seg1id,
        seg2id,
        p10,
        p11,
        p20,
        p21;
public:
    PastEdge(set<int> s,
             int ss1id, int ss2id,
             int pp10, int pp11, int pp20, int pp21)
        : inPlanar1(s), seg1id(ss1id), seg2id(ss2id),
          p10(pp10), p11(pp11), p20(pp20), p21(pp21) {}
    void operator()(int i);/*{
        inPlanar1.insert(i);
        Planar pl = Data::planars[i];
        vector<int> points = pl.getpoints(),
            segments = pl.getsegments();
        set<int> existsegments = pl.getexistsegments();
        for(auto i = points.begin(); i != points.end(); i++){
            if(*i == p20){
                *i = p10;
            }
            if(*i == p21){
                *i = p11;
            }
        }
        for(auto i = segments.begin(); i != segments.end(); i++){
            if(*i == seg2id){
                *i == seg1id;
            }
        }
        existsegments.erase(seg2id);
        existsegments.insert(seg1id);
        pl.setpoints(points);
        pl.setsegments(segments);
        pl.setexistsegments(existsegments);
        }*/
    set<int> getinPlanar1() const{
        return inPlanar1;
    }
};

#endif