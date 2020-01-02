#ifndef LINE
#define LINE

#include"BalanceTree.h"
#include<iostream>
#include"Point.h"
#include<set>
#include<map>
#include<algorithm>
#include"intersection.h"
using namespace std;

class GraphLine;
class GraphPoint;
class face;
class intersection;
class sweepLine;
//class AVLTree<GraphPoint>;

//extern double sweepLine::y;
class Line {
public:
    GraphPoint* ep[2];   //default oritaton ep[0] -> ep[1]
    bool Yin;
    Line(){}
    Line(GraphPoint* p1, GraphPoint* p2, bool b) : Yin(b){
        ep[0] = p1;
        ep[1] = p2;
        }
    Line(const Line& l) : Yin(l.Yin){
        ep[0] = l.ep[0];
        ep[1] = l.ep[1];
    }
    Line& operator=(const Line& l){
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
};
// Line::~Line(){}

class GraphLine : public Line {
    GraphLine* brl;
    GraphLine* nextl;
    GraphLine* prevl;
    GraphLine* faceleftmostl;
    bool faceleftmostlbool;
    GraphLine* leftl;
    face* gf;
    int s;                // Sign for where come from
    int identity;
    //GraphLine(const GraphLine&);
    //GraphLine& operator=(const GraphLine&);
public:
    GraphLine(){}
    GraphLine(const GraphLine&);
    GraphLine& operator=(const GraphLine&);
    GraphLine(GraphPoint& p1, GraphPoint& p2, int ii = 0, bool y = false, int ss = 0);/* : Line(&p1, &p2, y), s(i), faceleftmostlbool(false){
        nextl = 0;
        prevl = 0;
        faceleftmostl = 0;
        gf = 0;
        brl = 0;
        leftl =0;
        ep[0]->addnearl(this);
        ep[1]->addnearl(this);
        //   sweepLine::everyline.add(*this);
    }
    /*   GraphLine(const GraphLine& l) : Line(l), s(l.s), faceleftmostlbool(l.faceleftmostlbool){
        nextl = l.nextl;
        prevl = l.prevl;
        faceleftmostl = l.faceleftmostl;
        gf = l.gf;
        brl = l.brl;
        leftl = l.leftl;
        ep[0]->addnearl(this);
        ep[1]->addnearl(this);
        allLine.insert(this);
    }
    GraphLine& operator=(GraphLine& l){
        this->Line::operator=(l);
        faceleftmostlbool = l.faceleftmostlbool;
        nextl = l.nextl;
        prevl = l.prevl;
        faceleftmostl = l.faceleftmostl;
        gf = l.gf;
        s = l.s;
        brl = l.brl;
        leftl = l.leftl;
        ep[0]->addnearl(this);
        ep[1]->addnearl(this);
        }*/
    ~GraphLine();/*{
        nextl = 0;
        prevl = 0;
        faceleftmostl = 0;
        gf = 0;
        brl = 0;
        leftl = 0;
        ep[0]->remnearl(this);
        ep[1]->remnearl(this);
        //sweepLine::everyline.del(*this);
    }*/
    void updatebrl() ;//{ brl = ep[0]->findbrline(this);}
    void updateprevnextl();/*{
        nextl = ep[1]->findnextline(this);
        prevl = ep[0]->findprevline(this);
    }*/
    void updatefaceleftmostl();/*{
        if(faceleftmostlbool == true) return ;
        double d[2];
        d[0] = ep[0]->[0];
        d[1] = ep[0]->[1];
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
    /*        p = p->nextl;
        }
        faceleftmostlbool = true;
        p = p->nextl;
        while(p != this){
            p->faceleftmostl = markp;
            p->faceleftmostlbool = true;
            p = p->nextl;
        }
    }*/
    bool makesureOutbdOrIntbd(GraphLine* l);/*{
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
        }*/
    void updateleftl();
    void update();/*{
        updatebrl();
        updateprevnextl();
        updatefaceleftmostl();
        }*/
    bool operator<(GraphLine);
    bool operator>(GraphLine);

    // bool operator<(GraphLine &l){ return ::operator<(*this, l);}
    friend class intersection;
    friend class GraphPoint;
    friend class face;
    friend class sweepLine;
    // friend bool operator<(GraphLine l1, GraphLine l2);
};




/*bool comp(const GraphPoint* p1, const GraphPoint* p2){
    return (*p1) < (*p2);
    }*/
#endif
/*   static void updateleftl(){
     set<GraphPoint*> eventp = GraphPoint::eventpoint;
     set<GraphPoint*>::iterator pit;
     sort(eventp.begin(), eventp.end(), comp);
     for(pit = eventp.begin(); pit != eventp.end(); pit++){
     GraphPoint* p = (*pit);
     GraphPoint* q;
     set<GraphLine*>::iterator slit;
     for(slit = (p->nearl).begin(); slit != (p->nearl).end(); slit++){
     GraphLine* l = (*lit);
     if((*p) == (*(l->ep[0]))) q = l->ep[1];
     else q = l->ep[0];
     if((*p) < (*q)){
     map<GraphLine, vector<GraphLine*>>::iterator mit= orderline.find(*q);
     if(mit == orderline.end()) {cout << "updateleftl() error! mit"<< "\n"; }
     vector<GraphLine*> vl = mit->second;
     vector<GraphLine*>::iterator vlit;
     for(vlit = vl.begin(); vlit != vl.end(); vlit++)
     if(l == (*vlit)) vl.erase(vlit);
     if(vl.empty()) orderline.erase(*q);
     }
     if((*q) < (*p)){
     set<GraphLine*> 
     }
     }
     }
     }
*/
// void updateface(){}
    
