#ifndef SEGMENT_BOOLEAN
#define SEGMENT_BOOLEAN

#include"Point.h"
#include"Line.h"
#include"Direction.h"
#include"Tol.h"
#include"Data.h"
#include<vector>
#include<set>
#include<algorithm>
#include<iostream>


class Segment : public Line {
    int points[2];
    int id;
    std::set<int> inPlanar;
    std::set<int> inPlanar01, inPlanar10;
    int inYinset;
public:
    explicit Segment(int p0 = -1, int p1 = -1, int identity = -1,
                     const std::set<int> inP01 = std::set<int>(),
                     const std::set<int> inP10 = std::set<int>(),
            int inY = -1)
        : points{p0, p1}, id(identity), inPlanar01(inP01),
          inPlanar10(inP10), inYinset(inY) {
            inPlanar.insert(identity);
            for(auto i = inP01.begin(); i != inP01.end(); i++){
                inPlanar.insert(*i);
            }
            for(auto i = inP10.begin(); i != inP01.end(); i++){
                inPlanar.insert(*i);
            }
            if(p0 != -1 && p1 != -1){
                if(Data::points[p0] >
                   Data::points[p1]){
                    points[0] = p1;
                    points[1] = p0;
                    inPlanar01 = inP10;
                    inPlanar10 = inP01;
                }
                std::set<int> inSegment = Data::points[points[0]].getinSegment();
                inSegment.insert(id);
                Data::points[points[0]].setinSegment(inSegment);
                inSegment = Data::points[points[1]].getinSegment();
                inSegment.insert(id);
                Data::points[points[1]].setinSegment(inSegment);
            }
            Line::fixpoint = Data::points[points[0]];
            Line::direct = (Data::points[points[1]] - Data::points[points[0]]).unit();
            if(id != -1){
                Data::segments[id] = *this;
            }
        }
    Segment(const Segment& seg) : Line(seg), points{seg[0], seg[1]}, id(seg.id),
                                  inPlanar(seg.inPlanar),
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
        if((points[0] == -1) || (points[1] == -1)){
            std::cout << "Segment::setid() : " << id;
            int j;
            std::cin >> j;
        }
        std::set<int> inSegment = Data::points[points[0]].getinSegment();
        inSegment.insert(i);
        inSegment.erase(id);
        Data::points[points[0]].setinSegment(inSegment);
        inSegment = Data::points[points[1]].getinSegment();
        inSegment.insert(i);
        inSegment.erase(id);
        Data::points[points[1]].setinSegment(inSegment);
        id = i;
    }
    int getinYinset() const {
        return inYinset;
    }
    void setinYinset(const int i) {
        inYinset = i;
        if(id != -1){
            Data::segments[id] = *this;
        }
    }
    std::set<int> getinPlanar() const {
        return inPlanar;
    }
    void setinPlanar(const std::set<int>& v){
        inPlanar = v;
        if(id != -1){
            Data::segments[id] = *this;
        }
    }
    std::set<int> getinPlanar01() const {
        return inPlanar01;
    }
    void setinPlanar01(const std::set<int>& v){
        inPlanar01 = v;
        if(id != -1){
            Data::segments[id] = *this;
        }
    }
    std::set<int> getinPlanar10() const {
        return inPlanar10;
    }
    void setinPlanar10(const std::set<int>& v){
        inPlanar10 = v;
        if(id != -1){
            Data::segments[id] = *this;
        }
    }
    int operator[](const int i) const {
        return points[i];
    }
    void setendpoints(int i, int p) {
        if(i = 0){
            if(Data::points[p] < Data::points[points[1]]){
                std::set<int> inSegment = Data::points[points[0]].getinSegment();
                inSegment.erase(id);
                Data::points[points[0]].setinSegment(inSegment);
                inSegment = Data::points[p].getinSegment();
                inSegment.insert(id);
                Data::points[p].setinSegment(inSegment);
                points[0] = p;
                return;
            }
        }
        if(i = 1){
            if(Data::points[p] > Data::points[points[0]]){
                std::set<int> inSegment = Data::points[points[1]].getinSegment();
                inSegment.erase(id);
                Data::points[points[1]].setinSegment(inSegment);
                inSegment = Data::points[p].getinSegment();
                inSegment.insert(id);
                Data::points[p].setinSegment(inSegment);
                points[1] = p;
                return;
            }
        }
        else{
            std::cout << "setendpoints wrong:" << id << "\n";
            int k;
            std::cin >> k;
        }
        if(id != -1){
            Data::segments[id] = *this;
        }
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
