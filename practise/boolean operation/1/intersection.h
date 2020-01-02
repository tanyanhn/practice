#ifndef INTERSECTION
#define INTERSECTION




#include"Point.h"
#include"Line.h"
#include"BalanceTree.h"
#include<string>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<map>
using namespace std;

//const double eps = 0;

class GraphLine;
class GraphPoint;

class intersection {
    friend class GraphPoint;
    friend class GraphLine;
    friend class sweepLine;
    friend bool operator<(GraphLine, GraphLine);
    double Cross(const GraphPoint& p1, const GraphPoint& p2, const GraphPoint& p3, const GraphPoint& p4); /*{
        return (p2[0] - p1[0]) * (p4[1] -p3[1]) - (p2[1] - p1[1]) * (p4[0] - p3[0]);
        }*/
    double fArea(const GraphPoint& p1, const GraphPoint& p2, const GraphPoint& p3); /*{
        return fabs(Cross(p1, p2, p1, p3));
        }*/
    int Meet(const GraphPoint& p1, const GraphPoint& p2, const GraphPoint& p3, const GraphPoint& p4);/*{
        if( max(min(p1[0], p2[0]), min(p3[0], p4[0])) < min(max(p1[0], p2[0]), max(p3[0], p4[0]))
            && max(min(p1[1], p2[1]), min(p3[1], p4[1])) < min(max(p1[1], p2[1]), max(p3[1], p4[1]))
            && (Cross(p3, p2, p3, p4) * Cross(p3, p4, p3, p1) < -eps)
            && (Cross(p1, p4, p1, p2) * Cross(p1, p2, p1, p3) < -eps)) return -1;
        else if((!(Cross(p3, p2, p3, p4) > 0)) && (!(Cross(p3, p2, p3, p4) < 0)) &&
                (!(Cross(p3, p4, p3, p1) > 0)) && (!(Cross(p3, p4, p3, p1) < 0))) return 0;
        else return 1;
        }*/

    GraphPoint inter(const GraphPoint& p1, const GraphPoint& p2, const GraphPoint& p3, GraphPoint& p4);/*{
        double s1 = fArea(p1, p2, p3), s2 = fArea(p1, p2, p4);
        return GraphPoint((p4[0] * s1 + p3[0] * s2)/(s1 + s2), (p4[1] * s1 + p3[1] * s2)/(s1 + s2));
        }*/
    GraphPoint inter(const GraphLine& l1, const GraphLine& l2);/*{
        GraphPoint p1 = *(l1.ep[0]), p2 = *(l1.ep[1]), p3 = *(l2.ep[0]), p4 = *(l2.ep[1]);
        return inter(p1, p2, p3, p4);
        }*/
    int Meet(const GraphLine& l1, const GraphLine& l2);/*{
        GraphPoint p1 = *(l1.ep[0]), p2 = *(l1.ep[1]), p3 = *(l2.ep[0]), p4 = *(l2.ep[1]);
        return Meet(p1, p2, p3, p4);
        }*/
    /* GraphPoint intersect(GraphLine& l1, GraphLine &l2){
       GraphPoint p1 = *(l1.ep[0]), p2 = *(l1.ep[1]), p3 = *(l2.ep[0]), p4 = *(l2.ep[1]);
       if()
       }*/
};
class sweepLine{
    // static double y;
    typedef AVLTree<GraphPoint> ATP;
    typedef AVLTreeNode<GraphPoint> ATNP;
    // static ATP eventpoint;
    typedef AVLTree<GraphLine>  ATL;
    typedef AVLTreeNode<GraphLine>  ATNL;
    // static ATL everyline;
    // ATL orderline;
public:
      static double y;
    sweepLine()  {}
    friend class GraphPoint;
    friend class GraphLine;
    friend class intersection;
    friend bool operator<(GraphLine, GraphLine);
    static map<int, GraphLine> everyline;
    static ATP eventpoint;
    static ATL orderline;
    /*  bool operator<(GraphLine l1, GraphLine l2){
        double x1 = min(min(*(l1.ep[0])[0], *(l1.ep[1])[0]), min(*(l2.ep[0])[0], *(l2.ep[1])[0]));
        double x2 = max(max(*(l1.ep[0])[0], *(l1.ep[1])[0]), max(*(l2.ep[0])[0], *(l2.ep[1])[0]));
        GraphPoint a1(x1, y), a2(x2, y);
        GraphPoint l3(a1, a2);
        if(Meet(l1, l3) == 1) GraphPoint p1 = inter(l1, l3);
        else if(Meet(l1, l3) == 0){double p11 = min(*(l1.ep)[0], *(l1.ep)[1]);
        GraphPoint p1(p11, y);}
        else {cout << "operator< in sweepLine wrong "; exit(0);}
        if(Meet(l2, l3) == 1) GraphPoint p2 = inter(l2, l3);
        else if(Meet(l2, l3) == 0){double p21 = min(*(l2.ep)[0], *(l2.ep)[1]);
        GraphPoint p2(p21, y);}
        else {cout << "operator< in sweepLine wrong "; exit(0);}
        return p1 < p2;
        }
    */
};
//double sweepLine::y = 10000000;

//sweepLine::ATP sweepLine::eventpoint;
//sweepLine::ATL sweepLine::everyline;


#endif
