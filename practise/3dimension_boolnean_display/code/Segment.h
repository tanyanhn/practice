#ifndef SEGMENT_BOOLEAN
#define SEGMENT_BOOLEAN

#include"Point.h"
#include"Line.h"
#include"Direction.h"
#include"Tol.h"
#include"Data.h"
#include<vector>
#include<algorithm>
#include<iostream>


class Segment : public Line {
    int points[2];
    int id;
    std::vector<int> inPlanar01, inPlanar10;
    int inYinset;
public:
    explicit Segment(int p0 = -1, int p1 = -1, int identity = -1,
            const std::vector<int> inP01 = vector<int>(),
            const std::vector<int> inP10 = vector<int>(),
            int inY = -1)
        : points{p0, p1}, id(identity), inPlanar01(inP01),
          inPlanar10(inP10), inYinset(inY) {
        if(Data::points[p0] >
           Data::points[p1]){
            points[0] = p1;
            points[1] = p0;
            inPlanar01 = inP10;
            inPlanar10 = inP01;
        }
        Line::fixpoint = Data::points[points[0]];
        Line::direct = (Data::points[points[1]] - Data::points[points[0]]).unit();
    }
    Segment(const Segment& seg) : Line(seg), points{seg[0], seg[1]}, id(seg.id),
                                  inPlanar01(seg.inPlanar01), inPlanar10(seg.inPlanar10),
                                  inYinset(seg.inYinset) {}
    Segment& operator=(const Segment& seg){
        Segment temp(seg);
        std::swap(*this, temp);
        return *this;
    }
    ~Segment(){}
    int getid() const {
        return id;
    }
    void setid(const int i) {
        id = i;
    }
    int getinYinset() const {
        return inYinset;
    }
    void setinYinset(const int i) {
        inYinset = i;
    }
    std::vector<int> getinPlanar01() const {
        return inPlanar01;
    }
    void setinPlanar01(const std::vector<int>& v){
        inPlanar01 = v;
    }
    std::vector<int> getinPlanar10() const {
        return inPlanar10;
    }
    void setinPlanar10(const std::vector<int>& v){
        inPlanar10 = v;
    }
    int operator[](const int i) const {
        return points[i];
    }
    void setendpoints(int i, int p) {
        if(i = 0){
            if(Data::points[p] < Data::points[points[1]]){
                points[0] = p;
                return;
            }
        }
        if(i = 1){
            if(Data::points[p] > Data::points[points[0]]){
                points[1] = p;
                return;
            }
        }
        std::cout << "setendpoints wrong:" << id << "\n";
        int k;
        std::cin >> k;
    }
    /*int& operator[](const int i) {
        return points[i];
    }*/
    bool operator==(const Segment& seg1) const {
        return (points[0] == seg1[0] && points[1] == seg1[1]);
    }
    bool ifcontainPoint(const Point& p) const ;
    bool ifintersectionSegment(const Segment& seg2) const ;
    Point intersectionSegment(const Segment& seg2) const ;
    bool ifoverlapSegment(const Segment& seg2) const ;
    Segment overlapSegment(const Segment& seg2) const ;
};

#endif
