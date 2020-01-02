#include"BalanceTree.h"
#include<iostream>
#include"Point.h"
#include"Line.h"
#include"intersection.h"
#include<set>
#include<map>
#include<algorithm>
using namespace std;

class intersection;
class sweepLine;
class GraphLine;
class GraphPoint;
class face;
//class AVLTree<GraphPoint>;

/*class Line {
public:
    GraphPoint* ep[2];   //default oritaton ep[0] -> ep[1]
    bool Yin;
    Line(GraphPoint* p1, GraphPoint* p2, bool b) : Yin(b){
        ep[0] = p1;
        ep[1] = p2;
    }
    Line(const Line& l) : Yin(l.Yin){
        ep[0] = l.ep[0];
        ep[1] = l.ep[1];
    }
    Line& operator=(Line& l){
        ep[0] = l.ep[0];
        ep[0] = l.ep[1];
        Yin = l.Yin;
    }
    GraphPoint*& operator[](int i) {
        if(( i < 0)||(i > 1)){ cout << "Line[] wrong!"; exit(0);}
        return ep[i];
    }
    GraphPoint* const & operator[](int i) const  {
        if(( i < 0)||(i > 1)){ cout << "Line[] wrong!"; exit(0);}
        return ep[i];
    }
    virtual ~Line() = 0;
    };*/
Line::~Line(){}

/*class GraphLine : public Line {
    GraphLine* brl;
    GraphLine* nextl;
    GraphLine* prevl;
    GraphLine* faceleftmostl;
    bool faceleftmostlbool;
    GraphLine* leftl;
    face* gf;
    int s;                // Sign for where come from
    GraphLine(const GraphLine&);
    GraphLine& operator=(const GraphLine&);
    public:*/
GraphLine::GraphLine(GraphPoint& p1, GraphPoint& p2, int ii, bool y, int ss) : Line(&p1, &p2, y), s(ss), faceleftmostlbool(false), identity(ii){
        nextl = 0;
        prevl = 0;
        faceleftmostl = 0;
        gf = 0;
        brl = 0;
        leftl =0;
        //  ep[0]->addnearl(this);
        // ep[1]->addnearl(this);
        //   sweepLine::everyline.add(*this);
    }
GraphLine::GraphLine(const GraphLine& l) : Line(l), s(l.s), faceleftmostlbool(l.faceleftmostlbool), identity(l.identity){
         nextl = l.nextl;
         prevl = l.prevl;
         faceleftmostl = l.faceleftmostl;
         gf = l.gf;
         brl = l.brl;
         leftl = l.leftl;
         // ep[0]->addnearl(this);
         //  ep[1]->addnearl(this);
         // allLine.insert(this);
         }
GraphLine& GraphLine::operator=(const GraphLine& l){
         this->Line::operator=(l);
         faceleftmostlbool = l.faceleftmostlbool;
         nextl = l.nextl;
         prevl = l.prevl;
         faceleftmostl = l.faceleftmostl;
         gf = l.gf;
         s = l.s;
         brl = l.brl;
         leftl = l.leftl;
         identity = l.identity;
         return *this;
         //  ep[0]->addnearl(this);
         // ep[1]->addnearl(this);
         }
GraphLine::~GraphLine(){
        nextl = 0;
        prevl = 0;
        faceleftmostl = 0;
        gf = 0;
        brl = 0;
        leftl = 0;
        ep[0]->remnearl(this);
        ep[1]->remnearl(this);
        //sweepLine::everyline.del(*this);
    }
void GraphLine::updatebrl() { brl = ep[0]->findbrline(this);}
void GraphLine::updateprevnextl(){
        nextl = ep[1]->findnextline(this);
        prevl = ep[0]->findprevline(this);
    }
void GraphLine::updatefaceleftmostl(){
        if(faceleftmostlbool == true) return ;
        double d[2];
        d[0] = (*ep[0])[0];
        d[1] = (*ep[0])[1];
        GraphLine* markp = this;
        GraphLine* p = nextl;
        while(p != this){
            if((*(p->ep[0])) < (*(markp->ep[0]))){
                markp = p;
                d[0] = (*(p->ep[0]))[0];
                d[1] = (*(p->ep[0]))[1];
            }
            /*    if((*p->ep[0])[1] < d[1]){
                  markp = p;
                  d[0] = (*p->ep[0])[0];
                  d[1] = (*p->ep[0])[1];
                  }
                  else if((*p->ep[0])[1] = d[1]){
                  if((*p->ep[0])[0] < d[0]){
                  markp = p;
                  d[0] = (*p->ep[0])[0];
                  d[1] = (*p->ep[0])[1];
                  }
                  }*/
            p = p->nextl;
        }
        faceleftmostlbool = true;
        p = p->nextl;
        while(p != this){
            p->faceleftmostl = markp;
            p->faceleftmostlbool = true;
            p = p->nextl;
        }
    }
bool GraphLine::makesureOutbdOrIntbd(GraphLine* l){
        GraphLine* l1 = l->prevl;
        GraphLine* l2 = l;
        double d11, d12, d21, d22, d31, d32;
        d11 = (*(*l1).ep[0])[0];
        d12 = (*(*l1).ep[0])[1];
        d21 = (*(*l1).ep[1])[0];
        d22 = (*(*l1).ep[1])[1];
        d31 = (*(*l2).ep[1])[0];
        d32 = (*(*l2).ep[1])[1];
        if(((d12 - d22) * (d31 - d21) - (d11 - d21) * (d32 - d22)) > 0){
            return true;
        }
        return false;
    }
void GraphLine::update(){
        updatebrl();
        updateprevnextl();
        updatefaceleftmostl();
}
extern intersection sl;
//extern double sweepLine::y ;
bool GraphLine::operator<(GraphLine l2){
    GraphLine l1 = *this;
    double y = sweepLine::y;
    double x1 = min(min((*(l1.ep[0]))[0], (*(l1.ep[1]))[0]), min((*(l2.ep[0]))[0], (*(l2.ep[1]))[0]));
    double x2 = max(max((*(l1.ep[0]))[0], (*(l1.ep[1]))[0]), max((*(l2.ep[0]))[0], (*(l2.ep[1]))[0]));
    GraphPoint a1(x1, y), a2(x2, y);
    GraphLine l3(a1, a2);
    GraphPoint* p1, *p2;
    GraphPoint tp1, tp2;
    if(sl.Meet(l1, l3) == 1) { tp1 = sl.inter(l1, l3); p1 = &tp1;}
    else if(sl.Meet(l1, l3) == 0){double p11 = min((*(l1.ep[0]))[0], (*(l1.ep[1]))[0]);
        tp1 = GraphPoint(p11, y);  p1 = &tp1;}
    else {cout << "operator< in sweepLine wrong "; exit(0);}
    if(sl.Meet(l2, l3) == 1) { tp2 = sl.inter(l2, l3); p2 = &tp2;}
    else if(sl.Meet(l2, l3) == 0){double p21 = min((*(l2.ep[0]))[0], (*(l2.ep[1]))[0]);
        tp2 = GraphPoint(p21, y);  p2 = &tp2;}
    else {cout << "operator< in sweepLine wrong "; exit(0);}
    return (*p1 < *p2);
}

bool GraphLine::operator>(GraphLine l2){
    return l2 < *this;
}
/*
bool comp(const GraphPoint* p1, const GraphPoint* p2){
    return (*p1) < (*p2);
}

*/
void GraphLine::updateleftl(){
    AVLTreeNode<GraphLine>* p = sweepLine::orderline.find(*this);
    if((p->data).faceleftmostl != this) leftl = 0;
    else {
        GraphLine l = sweepLine::orderline.findprevnode(p)->data;
        leftl = &((sweepLine::everyline.find(l.identity))->second);
    }
}
