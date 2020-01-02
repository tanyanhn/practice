#ifndef POINT
#define POINT

#include"Line.h"
#include"BalanceTree.h"
#include"Sweepline.h"
#include<utility>
#include<vector>
#include<math.h>
#include<iostream>
#include<stdlib.h>
using namespace std;

class Point  {
    double coord[2];
    int identity;
    AVLTree<pair<double, vector<int>>> nearline;
public:
    explicit Point(const double i0 = 0, const double i1 = 0, const int ident = -1){
        coord[0] = i0;
        coord[1] = i1;
        identity = ident;
        // AVLTree<pair<double, vector<int>>> nearline;
    }
    Point(const Point& p) : nearline(){
        coord[0] = p[0];
        coord[1] = p[1];
        identity = p.identity;
        nearline = p.nearline;
    }
    Point& operator=(const Point& p){
        coord[0] = p[0];
        coord[1] = p[1];
        identity = p.identity;
        nearline = p.nearline;
        return *this;
    }
    ~Point(){}
    double& operator[](const int index){
        if(index < 0 || index > 1) cout << "operator[] wrong";
        return coord[index];
    }
    const double& operator[](const int index) const{
        if(index < 0 || index > 1) cout << "opearotr[] const wrong";
        return coord[index];
    }
    Point operator-(const Point& p) const {
        return Point(coord[0] - p[0], coord[1] - p[1]);
    }
    bool operator==(const Point& p) const ;/*{
        if(fabs(coord[0] - p[0]) < Sweepline::tol && fabs(coord[1] - p[1]) < Sweepline::tol) return true;
        else return false;
    }*/
    bool operator<(const Point& p) const ;/*{
        if(coord[1] < p[1] - Sweepline::tol){
            return true;
        }
        else if(coord[1] < p[1] + Sweepline::tol && coord[0] < p[0] - Sweepline::tol) {
            return true;
        }
        return false;
        }*/
    bool operator>(const Point& p) const {
        return p < *this;
    }
    int getidentity() const { return identity;}
    void setidentity(const int& i) { identity=i;}
    double dot(const Point& p) const {
        return (coord[0] * p[0] + coord[1] * p[1]);
    }
    double cross(const Point& p) const {
        return(coord[0] * p[1] - coord[1] * p[0]);
    }
    Line nextline(const Line&);
    void addnearline(const Line&);
    void delnearline(const Line&);
    friend ostream& operator<<(ostream& os, const Point& p){
        os << p[0] << "\t\t\t" << p[1] << endl;
    }
    friend class Sweepline;
    friend class Line;
};


#endif