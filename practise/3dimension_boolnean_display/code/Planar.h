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

class Data;
class Segment;
class Flat;

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
    Planar(std::vector<int> p, std::vector<int> s, int identity = -1, int inF = -1, int inY = -1);
    /*     : Flat(Data::points[p[0]], Data::points[p[1]], Data::points[p[2]]),
          points(p), segments(s), id(identity), inFace(inF), inYinset(inY) {
        for(auto i = points.begin(); i != points.end(); i++){
            existpoints.insert(*i);
        }
        for(auto i = segments.begin(); i != segments.end(); i++){
            existsegments.insert(*i);
        }
    }*/
    Planar(const Planar& pl);/* :
        Flat(pl),
        points(pl.points), segments(pl.segments),
        existpoints(pl.existpoints), existsegments(pl.existsegments),
        id(pl.id), inFace(pl.inFace), inYinset(pl.inYinset) {}
                             */
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
        if(id != -1){
            Data::planars[id] = *this;
        }
    }
    std::vector<int> getsegments() const {
        return segments;
    }
    void setsegments(const std::vector<int>& vs) {
        segments = vs;
        if(id != -1){
            Data::planars[id] = *this;
        }
    }
    std::set<int> getexistpoints() const {
        return existpoints;
    }
    void setexistpoints(const std::set<int>& sp) {
        existpoints = sp;
        if(id != -1){
            Data::planars[id] = *this;
        }
    }
    std::set<int> getexistsegments() const {
        return existsegments;
    }
    void setexistsegments(const std::set<int>& ss) {
        existsegments = ss;
        if(id != -1){
            Data::planars[id] = *this;
        }
    }
    int getid() const {
        return id;
    }
    void setid(const int i){
        id = i;
        if(id != -1){
            Data::planars[id] = *this;
        }
    }
    int getinFace() const {
        return inFace;
    }
    void setinFace(const int i){
        inFace = i;
        if(id != -1){
            Data::planars[id] = *this;
        }
    }
    int getinYinset() const {
        return inYinset;
    }
    void setinYinset(const int i){
        inYinset = i;
        if(id != -1){
            Data::planars[id] = *this;
        }
    }
    bool ifcontainPoint(const Point&) const;
    bool ifcontainSegment(const Segment&) const;
    bool ifcontainPlanar(const Planar&) const;
    bool ifintersectionSegment(const Segment&) const;
    Point intersectionSegment(const Segment&) const;
    // double angleBetweenPlanars(const Planar&, const Direction&) const;
    //bool ifintersectionPlanar(const Planar&) const;
    //Segment intersectionPlanar(const Planar&) const;
    //std::vector<Planar> trianglulation();
};

#endif