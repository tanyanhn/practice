#ifndef PLANAR_BOOLEAN
#define PLANAR_BOOLEAN

#include"Point.h"
#include"Segment.h"
#include"Flat.h"
#include"Direction.h"
#include"Data.h"
#include<vector>
#include<utility>
#include<set>

class Planar : public Flat {
    std::vector<int> points;
    std::vector<int> segments;
    std::set<int> existpoints;
    std::set<int> existsegments;
    int id;
    int inFace;
    int inYinset;
public:
    Planar(){}
    Planar(std::vector<int> p, std::vector<int> s, int identity = -1, int inF = -1, int inY = -1) : points(p), segments(s), id(identity), inFace(inF), inYinset(inY) {
        for(auto i = points.begin(), i != points.end(), i++){
            existpoints.insert(*i);
        }
        for(auto i = segments.begin(), i != segments.end(), i++){
            existsegments.insert(*i);
        }
    }
    Planar(const Planar& pl) : points(pl.points), segments(pl.segments), existpoints(pl.existpoints), existsegments(pl.existsegments), id(pl.ed), inFace(pl.inFace), inYinset(pl.inYinset) {}
    Planar& operator=(const Planar& pl) {
        Planar temp(pl);
        std::swap(*this, temp);
        return *this;
    }
    std::vector<int> getpoints() const {
        return points;
    }
    void setpoints(const std::vector<int>& vp) {
        points = vp;
    }
    std::vector<int> getsegments() const {
        return segments;
    }
    void setsegments(const std::vector<int>& vs) {
        segments = vs;
    }
    std::set<int> getexistpoints() const {
        return existpoints;
    }
    void setexistpoints(const std::set<int>& sp) {
        existpoints = sp;
    }
    std::set<int> getexistsegments() const {
        return existsegments;
    }
    void setexistsegment(const std::set<int>& ss) {
        existsegment = ss;
    }
    int getid() const {
        return id;
    }
    void setid(const int i){
        id = i;
    }
    int getinFace() const {
        return inFace;
    }
    void setinFace(const int i){
        inFace = i;
    }
    int getinYinset() const {
        return inYinset;
    }
    void setinYinset(const int i){
        inYinset = i;
    }
    bool ifcontainPoint(const Point&) const;
    bool ifcontainSegment(const Segment&) const;
    bool ifintersectionSegment(const Segment&) const;
    Point intersectionSegment(const Segment&) const;
    bool ifintersectionPlanar(const Planar&) const;
    Segment intersectionPlanar(const Planar&) const;
    //std::vector<Planar> trianglulation();
};

#endif