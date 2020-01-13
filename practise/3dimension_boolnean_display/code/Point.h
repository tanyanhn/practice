#ifndef POINT_BOOLEAN
#define POINT_BOOLEAN

#include<iostream>
#include<math.h>
#include<vector>
#include<set>
#include"Direction.h"
#include"Tol.h"
using namespace std;

class Point{
    double coord[3];
    int id;
    set<int> inSegment;
    int inYinset;
public:
    Point() : coord{0, 0, 0}, id(-1), inSegment(set<int>()), inYinset(-1) {}
    Point(const double x, const double y, const double z, const int identity = -1, const set<int> &v = set<int>(), const int it = -1);
    Point(const Point&);
    Point& operator=(const Point&);
    ~Point(){}
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
    set<int> getinSegment() const {
        return inSegment;
    }
    void setinSegment(const set<int>& v) {
        inSegment = v;
    }
    const double operator[](const int i) const {
        if(i < 0 || i > 2){
            cout << id << " : " << i << " out of range";
            char a;
            cin >> a;
        }
        return coord[i];
    }
    double& operator[](const int i){
        if(i < 0 || i > 2){
            cout << id << " : " << i << " out of range";
            char a;
            cin >> a;
        }
        return coord[i];
    }
    Direction operator-(const Point& q) const {
        return Direction(coord[0] - q.coord[0],
                         coord[1] - q.coord[1],
                         coord[2] - q.coord[2]);
    }
    Point operator+(const Direction& d) const {
        return Point(coord[0] + d[0],
                     coord[1] + d[1],
                     coord[2] + d[2]);
    }
    bool operator==(const Point& q) const {
        return
            (fabs(coord[0] - q.coord[0]) < Tol::t) &&
            (fabs(coord[1] - q.coord[1]) < Tol::t) &&
            (fabs(coord[2] - q.coord[2]) < Tol::t);
    }
    bool operator<(const Point& q) const ;
    bool operator>(const Point& q) const {
        return q < *this;
    }
};

#endif