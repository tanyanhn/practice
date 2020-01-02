#ifndef POINT
#define POINT

#include"BalanceTree.h"
#include<vector>
#include"Line.h"
#include<set>
#include<iostream>
#include<math.h>
#include"intersection.h"
using namespace std;

class GraphPoint;
class GraphLine;

class Point{
public:
    double coord[2];
    Point(){}
    Point(double d1,double d2){ coord[0] = d1; coord[1] = d2;}
    Point& operator=(const Point& p){ coord[0] = p[0]; coord[1] = p[1];}
    Point(const Point& p){ coord[0] = p[0]; coord[1] = p[1];}
    virtual ~Point() = 0;
    double& operator[](int i){
        if((i < 0)||(i > 1)) {cout << "Point[] wrong!"; exit(0) ;}
        return coord[i];
    }
    const double& operator[](int i) const {
        if((i < 0)||(i > 1)) {cout << "Point[] wrong!"; exit(0) ;}
        return coord[i];
    }
};
//Point::~Point(){}

class GraphPoint : public Point {
    set<GraphLine*> nearl;
    // GraphPoint(const GraphLine&);
    // GraphPoint& operator=(const GraphLine&);
public:
    GraphPoint(){ set<GraphLine*> nearl;}
    GraphPoint(const GraphPoint&);
    GraphPoint& operator=(const GraphPoint&);
    GraphPoint(double d1, double d2) ;/*: Point(d1,d2) {
        set<GraphLine*> nearl;
        //sweepLine::eventpoint.add(*this);
        } */
    /*GraphPoint(const GraphPoint& p) : Point(p){
      set<GraphLine*> nearl;
      set<GraphLine*>::iterator it;
      for(it = p.nearline().begin(); it != p.nearline().end(); it++){
      nearl.insert(*it);
      }
      }
   
      GraphPoint& operator=(GraphPoint& p) {
      coord[0] = p[0];
      coord[1] = p[1];
      set<GraphLine*>::iterator it;
      nearl.erase(nearl.begin(), nearl.end());
      for(it = p.nearline().begin(); it != p.nearline().end(); it++){
      nearl.insert(*it);
      }
      }*/
    ~GraphPoint();/*{ //sweepLine::eventpoint.del(*this);
        nearl.erase(nearl.begin(), nearl.end()); }*/
    double& operator[](int i);/*{
        if((i < 0)||(i > 1)) {cout << "Point[] wrong!"; exit(0) ;}
        return coord[i];
        }*/
    const double& operator[](int i) const ;/*{
        if((i < 0)||(i > 1)) {cout << "Point[] wrong!"; exit(0) ;}
        return coord[i];
        }*/
    bool operator<(const GraphPoint& p) const ;/*{
        if(coord[1] < p.coord[1] - 1e-10){
            return true;
        }
        else if((coord[1] > p.coord[1] - 1e-10) && (coord[1] < p.coord[1] + 1e-10) ){
            if(coord[0] < p.coord[0] - 1e-10){
                return true;
            }
            
        }
        return false;
        }*/
    bool operator>(const GraphPoint& p) const ;/*{
        if(coord[1] > p.coord[1] + 1e-10){
            return true;
        }
        else if((coord[1] > p.coord[1] - 1e-10) && (coord[1] < p.coord[1] + 1e-10) ){
            if(coord[0] > p.coord[0] + 1e-10){
                return true;
            }
            
        }
        return false;
    }*/
    bool operator==(const GraphPoint& p) const ;/*{
        if((fabs(coord[1] - p.coord[1]) < 1e-10) && (fabs(coord[0] - p.coord[0]) < 1e-10))
            return true;
        return false;
        }*/
    GraphLine* findnextline(GraphLine* l); /*{
        GraphLine* lp = findsmallangle(l, 1);
        return lp;
        }*/
    GraphLine* findprevline(GraphLine* l); /*{
        GraphLine* lp = findsmallangle(l, 2);
        }*/
    GraphLine* findbrline(GraphLine* l); /*{
        if(this != (*l).ep[0]) {
            cout << "in findbrline wrong argument!" << endl;
            exit(0);
        }
        GraphPoint* p = (*l).ep[1];
        set<GraphLine*>::iterator it;
        for(it = nearl.begin(); it != nearl.end(); it++){
            if(p == (**it).ep[0]) return (*it);
        }
        cout << "findbrline don't find!" << endl;
        exit(0);
        }*/
    const set<GraphLine*>& nearline() const ;//{ return nearl;}
    set<GraphLine*>& nearline(); //{ return nearl;}
    void addnearl(GraphLine* l); //{ nearl.insert(l); }
    void remnearl(GraphLine* l); //{ nearl.erase(l); }
    GraphLine* findsmallangle(GraphLine* l, int o);  // when o = 1, find next
    // when o = 2, find previous, others undefine.
    friend ostream& operator<<(ostream& os, GraphPoint p){
        return os << p.coord[0] << ", " << p.coord[1];
    }
    friend class GraphLine;
    friend class sweepLine;
    friend class intersection;
/*  GraphLine* findsmallangle(GraphLine* l, int o){
    if(o == 1){
    if((*l).ep[1] != this) {
    cout << "findsmallangle o l wrong!"<< endl;
    exit(0);
    }
    }
    else if(o == 2){
    if((*l).ep[0] != this){
    cout << "findsmallangle o l wrong!"<< endl;
    exit(0);
    }
    }
    else {
    cout << "findsmallangle o wrong!" << "\n";
    exit(0);
    }
    set<GraphLine*>::iterator it,aim;
    double x1 = -2;
    double x2 = -2;
    GraphLine* g1 = 0;
    GraphLine* g2 = 0;
    for(it = nearl.begin(); it != nearl.end(); it++){
    if(o == 1){
    if((**it).ep[0] == this){
    double d11, d12, d21, d22, d31, d32;
    d11 = (*l).ep[0][0];
    d12 = (*l).ep[0][1];
    d21 = (*l).ep[1][0];
    d22 = (*l).ep[1][1];
    d31 = (**it).ep[1][0];
    d32 = (**it).ep[1][1];
    double e1 = (d11 - d21) * (d11 - d21) + (d12 - d22) * (d12 - d22);
    e1 = sqrt(e1);
    double e2 = (d31 - d21) * (d31 - d21) + (d32 - d22) * (d32 - d22);
    e2 = sqrt(e2);
    if(((d12 - d22) * (d31 - d21) - (d11 - d21) * (d32 - d22)) > 0) {
    if(((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2) > x1){
    x1 = ((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2);
    g1 = (*it);
    }
    }
    else{
    if(((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2) < x2){
    x2 = ((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2);
    g2 = (*it);
    }
    }
    }
    }
    else if( o == 2){
    if((**it).ep[1] == this){
    double d11, d12, d21, d22, d31, d32;
    d11 = (**it).ep[0][0];
    d12 = (**it).ep[0][1];
    d21 = (*l).ep[0][0];
    d22 = (*l).ep[0][1];
    d31 = (*l).ep[1][0];
    d32 = (*l).ep[1][1];
    double e1 = (d11 - d21) * (d11 - d21) + (d12 - d22) * (d12 - d22);
    e1 = sqrt(e1);
    double e2 = (d31 - d21) * (d31 - d21) + (d32 - d22) * (d32 - d22);
    e2 = sqrt(e2);
    if(((d12 - d22) * (d31 - d21) - (d11 - d21) * (d32 - d22)) > 0) {
    if(((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2) > x1){
    x1 = ((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2);
    g1 = (*it);
    }
    }
    else{
    if(((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2) < x2){
    x2 = ((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2);
    g2 = (*it);
    }
    }
    }
    }
    }
                
    }*/
};


/*
GraphLine* GraphPoint::findsmallangle(GraphLine* l, int o){
    if(o == 1){
        if((*l).ep[1] != this) {
            cout << "findsmallangle o l wrong!"<< endl;
            exit(0);
        }
    }
    else if(o == 2){
        if((*l).ep[0] != this){
            cout << "findsmallangle o l wrong!"<< endl;
            exit(0);
        }
    }
    else {
        cout << "findsmallangle o wrong!" << "\n";
        exit(0);
    }
    set<GraphLine*>::iterator it,aim;
    double x1 = -2;
    double x2 = -2;
    GraphLine* g1 = 0;
    GraphLine* g2 = 0;
    for(it = nearl.begin(); it != nearl.end(); it++){
        if(o == 1){
            if((**it).ep[0] == this){
                double d11, d12, d21, d22, d31, d32;
                d11 = (*(*l).ep[0])[0];
                d12 = (*(*l).ep[0])[1];
                d21 = (*(*l).ep[1])[0];
                d22 = (*(*l).ep[1])[1];
                d31 = (*(**it).ep[1])[0];
                d32 = (*(**it).ep[1])[1];
                double e1 = (d11 - d21) * (d11 - d21) + (d12 - d22) * (d12 - d22);
                e1 = sqrt(e1/2);
                double e2 = (d31 - d21) * (d31 - d21) + (d32 - d22) * (d32 - d22);
                e2 = sqrt(e2/2);
                if(((d12 - d22) * (d31 - d21) - (d11 - d21) * (d32 - d22)) > 0) {
                    if(((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2) > x1){
                        x1 = ((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2);
                        g1 = (*it);
                    }
                }
                else{
                    if(((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2) < x2){
                        x2 = ((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2);
                        g2 = (*it);
                    }
                }
            }
        }
        else if( o == 2){
            if((**it).ep[1] == this){
                double d11, d12, d21, d22, d31, d32;
                d11 = (*(**it).ep[0])[0];
                d12 = (*(**it).ep[0])[1];
                d21 = (*(*l).ep[0])[0];
                d22 = (*(*l).ep[0])[1];
                d31 = (*(*l).ep[1])[0];
                d32 = (*(*l).ep[1])[1];
                double e1 = (d11 - d21) * (d11 - d21) + (d12 - d22) * (d12 - d22);
                e1 = sqrt(e1);
                double e2 = (d31 - d21) * (d31 - d21) + (d32 - d22) * (d32 - d22);
                e2 = sqrt(e2);
                if(((d12 - d22) * (d31 - d21) - (d11 - d21) * (d32 - d22)) > 0) {
                    if(((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2) > x1){
                        x1 = ((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2);
                        g1 = (*it);
                    }
                }
                else{
                    if(((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2) < x2){
                        x2 = ((d11 - d21) * (d31 - d21) + (d12 - d22) * (d32 - d22))/(e1 * e2);
                        g2 = (*it);
                    }
                }
            }
        }
    }
    if(x1 != -2) return g1;
    else if( x2 != -2) return g2;
    else {
        cout << "nextl don't have line! in findsmallangle()!"<< endl;
        exit(0);
    }
}

*/
#endif
