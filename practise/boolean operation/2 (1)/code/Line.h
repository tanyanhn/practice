#ifndef LINE
#define LINE

#include"Point.h"
#include"Sweepline.h"
#include"Jordanline.h"
#include<iostream>
using namespace std;


class Point;
class Sweepline;


class Line  {
    int lp[2];
    int identity;
    int injordanline;
    int leftline;
    int inspajor;
    bool IfInOtherYinset;
public:
    explicit Line(const int lp0 = 0, const int lp1 =0, const int ident = -1, const int spajor = -1) : identity(ident), injordanline(-2), inspajor(spajor), IfInOtherYinset(true), leftline(-2) {
        lp[0] = lp0;
        lp[1] = lp1;
    }
    Line(const Line& l) : identity(l.identity), injordanline(l.injordanline), inspajor(l.inspajor), IfInOtherYinset(l.IfInOtherYinset), leftline(l.leftline){
        lp[0] = l[0];
        lp[1] = l[1];
    }
    Line& operator=(const Line& l){
        lp[0] = l[0];
        lp[1] = l[1];
        identity = l.identity;
        inspajor = l.inspajor;
        injordanline = l.injordanline;
        leftline = l.leftline;
        IfInOtherYinset = l.IfInOtherYinset;
        return *this;
    }
    ~Line(){}
    int& operator[](const int i){
        if(i < 0 || i > 1) cout << "Line::operator[] wrong";
        return lp[i];
    }
    const int operator[](const int i) const {
        if(i < 0 || i > i) cout << "Line::operator[] wrong";
        return lp[i];
    }
    const int getidentity() const {
        return identity;
    }
    void setidentity(const int i){
        identity = i;
    }
    const int getinjordanline() const {
        return injordanline;
    }
    void setinjordanline(const int i) {
        injordanline = i;
    }
    const int getinspajor() const {
        return inspajor;
    }
    void setinspajor(const int i){
        inspajor = i;
    }
    const int getleftline() const {
        return leftline;
    }
    void setleftline(const int i){
        leftline = i;
    }
    const bool getIfInOtherYinset() const {
        return IfInOtherYinset;
    }
    void setIfInOtherYinset(const bool b){
        IfInOtherYinset = b;
    }
    const double angle(const Point&) const ;
    const int ifintheline(const Point&) const ;
    const bool ifintersection(const Line&) const;
    const Point intersection(const Line&) const;
    const bool operator<(const Line&) const ;
    const bool operator>(const Line&) const ;
    static void generator();
};

#endif