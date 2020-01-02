#include"Point.h"
#include"Line.h"
#include"BalanceTree.h"
#include<string>
#include"intersection.h"
#include<fstream>
#include<iomanip>
#include<algorithm>
using namespace std;

const double eps = 1e-10;



/*class intersection {
    friend class GraphPoint;
    friend class GraphLine;
    friend class sweepLine;*/
double intersection::Cross(const GraphPoint& p1, const GraphPoint& p2, const GraphPoint& p3, const GraphPoint& p4){
        return (p2[0] - p1[0]) * (p4[1] -p3[1]) - (p2[1] - p1[1]) * (p4[0] - p3[0]);
    }
double intersection::fArea(const GraphPoint& p1, const GraphPoint& p2, const GraphPoint& p3){
        return fabs(Cross(p1, p2, p1, p3));
    }
int intersection::Meet(const GraphPoint& p1, const GraphPoint& p2, const GraphPoint& p3, const GraphPoint& p4){
        if( max(min(p1[0], p2[0]), min(p3[0], p4[0])) > min(max(p1[0], p2[0]), max(p3[0], p4[0]))
            || max(min(p1[1], p2[1]), min(p3[1], p4[1])) > min(max(p1[1], p2[1]), max(p3[1], p4[1]))
            || (Cross(p3, p2, p3, p4) * Cross(p3, p4, p3, p1) < -eps)
            || (Cross(p1, p4, p1, p2) * Cross(p1, p2, p1, p3) < -eps)) return -1;
        else if((!(Cross(p3, p2, p3, p4) > eps)) && (!(Cross(p3, p2, p3, p4) < -eps)) &&
                (!(Cross(p3, p4, p3, p1) > eps)) && (!(Cross(p3, p4, p3, p1) < -eps))) return 0;
        else return 1;
    }

GraphPoint intersection::inter(const GraphPoint& p1, const GraphPoint& p2, const GraphPoint& p3, GraphPoint& p4){
        double s1 = fArea(p1, p2, p3), s2 = fArea(p1, p2, p4);
        return GraphPoint((p4[0] * s1 + p3[0] * s2)/(s1 + s2), (p4[1] * s1 + p3[1] * s2)/(s1 + s2));
    }
GraphPoint intersection::inter(const GraphLine& l1, const GraphLine& l2){
        GraphPoint p1 = *(l1.ep[0]), p2 = *(l1.ep[1]), p3 = *(l2.ep[0]), p4 = *(l2.ep[1]);
        return inter(p1, p2, p3, p4);
    }
int intersection::Meet(const GraphLine& l1, const GraphLine& l2){
    GraphPoint p1 = *(l1.ep[0]),
        p2 = *(l1.ep[1]),
        p3 = *(l2.ep[0]),
        p4 = *(l2.ep[1]);
        return Meet(p1, p2, p3, p4);
    }
    /* GraphPoint intersect(GraphLine& l1, GraphLine &l2){
       GraphPoint p1 = *(l1.ep[0]), p2 = *(l1.ep[1]), p3 = *(l2.ep[0]), p4 = *(l2.ep[1]);
       if()
       }*/
//};
