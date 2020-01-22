#include"Triangulation.h"
//#include"Data.h"
#include"Tol.h"
#include"Direction.h"
#include"Line.h"
#include"DatastructureHead.h"
#include"FunctorHead.h"
#include"STLHead.h"
//#include<vector>
//#include<set>
//#include<map>
//#include<math.h>
//#include<utility>
//#include<iostream>
//#include<algorithm>

using namespace std;



vector<Planar> Triangulation::operator()(Planar& p) {
    pl = p;
    (*Tol::outside) = p.getnormaldirect();
    Flat f;
    if(p.getnormaldirect().cross(Direction(0, 0, 1)).norm() < (Tol::t)){
        f.setnormaldirect(Direction(0, 1, 0));
    }
    else{
        f.setnormaldirect(Direction(0, 0, 1));
    }
    Line sweepline = f.intersectionFlat(p);
    if(sweepline.getfixpoint() > (sweepline.getfixpoint() + sweepline.getdirect())) {
        sweepline.setdirect(sweepline.getdirect() * (-1));
    }
    (*Tol::l) = sweepline;
    makeMonotone();
    vector<Planar> yMonotones = generatorPolygen();
    vector<Planar> triangles;
    for(auto i = yMonotones.begin(); i != yMonotones.end(); i++){
        vector<Planar> partTriangle = TriangulateMonotonePolygon(*i);
        copy(partTriangle.begin(), partTriangle.end(), triangles.end());
    }
    return triangles;
}


void Triangulation::makeMonotone(){
    //Planar newpl = this->pl;
    set<Point> allPoints;
    set<int> allSegments = pl.getexistsegments();
    //map<int, set<Segment>::iterator> sweepflatposition;
    for(auto i = allSegments.begin(); i != allSegments.end(); i++){
        Segment seg = Data::segments[*i];
        allPoints.insert(Data::points[seg[0]]);
        allPoints.insert(Data::points[seg[1]]);
    }
    map<double, int, DoubleComparer> nearSegment;
    auto i = --allPoints.end();
    while(1){
        Point p = *i;
        Tol::l->setfixpoint(p);
        Line sweepline = *Tol::l;
        /*
        if(sweepline.getdirect()
           .cross(Tol::f.getnormaldirect())
           .dot(pl.getnormaldirect()) < 0) {
            sweepline.setdirect(sweepline.getdirect() * (-1));
        }
        */
        nearSegment.clear();
        set<int> inSegments = p.getinSegment();
        for(auto j = inSegments.begin(); j != inSegments.end(); j++){
            Segment seg = Data::segments[*j];
            Point p0 = Data::points[seg[0]],
                p1 = Data::points[seg[1]];
            if(p1.getid() == p.getid()){
                swap(p0, p1);
            }
            Direction segdirect = p1 - p0;
            set<int> inPlanar = seg.getinPlanar();
            if(inPlanar.find(pl.getid()) != inPlanar.end()){
                nearSegment[sweepline.getdirect().angle(segdirect, pl.getnormaldirect())]
                    = seg.getid();
            }
        }
        if(nearSegment.empty()){
            cout << "Triangulation::makeMonotone nearSegment.empty is true : " << pl.getid()
                 << " : " << p.getid();
            int k;
            cin >> k;
        }
        bool leftmost = false;
        set<Segment>::iterator lsegit;
        int leftseg = -1;
        double leftsegangle = 0;
        for(auto j = nearSegment.begin(); j != nearSegment.end(); j++){
            if(j->first >= 0 && j->first < M_PI && j->first > leftsegangle){
                leftsegangle = j->first;
                leftseg = j->second;
            }
        }
        auto lit = sweepflatposition[leftseg];
        if(lit == sweepflat.begin()){
            leftmost = true;
        }
        else{
            lit--;
            lsegit = lit;
        }
        if(nearSegment.size() == 1){
            auto j = nearSegment.begin();
            set<Segment>::iterator segit = sweepflat.insert(Data::segments[j->second]).first;
            sweepflatposition[j->second] = segit;
            if(!(j->first >= M_PI)){
                if(leftmost == false){
                    handleSplitVertex(p, segit, lsegit);
                }
                else{
                    cout << "shouldn't exist situation segment exist outside triangle :"
                         << pl.getid() << " : " << p.getid();
                    int k;
                    cin >> k;
                }
            }
            else {
                if(leftmost == false){
                    handleMergeVertex(p, segit, lsegit);
                }
                else{
                    cout << "shouldn't exist situation segment exist outside triangle :"
                         << pl.getid() << " : " << p.getid();
                    int k;
                    cin >> k;
                }
            }
            if(j->first < M_PI){
                sweepflatposition.erase(j->second);
                sweepflat.erase(segit);
                helper.erase(j->second);
            }
            else{
                helper[j->second] = make_pair(split, p.getid());
            }
        }
        else {
            for(auto j = nearSegment.begin(); j != nearSegment.end(); j++){
                if(j->first >= M_PI){
                    auto it = sweepflat.insert(Data::segments[j->second]).first;
                    sweepflatposition[j->second] = it;
                }
            }
            for(auto j = nearSegment.begin(); j != nearSegment.end(); j++){
                set<Segment>::iterator seg1it, seg2it;
                seg1it = sweepflatposition[j->second];
                /*
                  if(sweepflatposition.find(j->second) != sweepflat.end()){
                  seg1it = sweepflatposition[j->second];
                  }
                  else{
                  seg1it = sweepflat.insert(Data::segments[j->second]);
                  sweepflatposition[j->second] = seg1it;
                  }
                */
                auto j2 = ++j;
                if(j2 == nearSegment.end()){
                    j2 = nearSegment.begin();
                }
                seg2it = sweepflatposition[j2->second];
                /*
                  if(sweepflatposition.find(j2->second) != sweepflat.end()){
                  seg2it = sweepflatposition[j2->second];
                  }
                  else {
                  seg2it = sweepflat.insert(Data::segments[j2->second]);
                  sweepflatposition[j2->second] = seg2it;
                  }
                */
                if((j->first >= M_PI) && (j2->first > M_PI) && (j2->first > j->first)){
                    handleStartVertex(p, seg1it);
                    //helper[j->second] = make_pair(start, p.getid());
                    //sweepflat.erase(seg2it);
                    //sweepflatposition.erase(j2->second);
                }
                else if((j->first < M_PI) && (j2->first < M_PI) && (j2->first > j->first)){
                    handleEndVertex(p, seg2it);
                    //sweepflat.erase(seg2it);
                    //sweepflatposition.erase(j2->second);
                    //helper.erase(j2->second);
                }
                else if((j->first > M_PI) && (j2->first >= M_PI) && (j2->first < j->first)){
                    if(leftmost == false){
                        handleSplitVertex(p, seg1it, lsegit);
                        //helper[j->second] = make_pair(split, p.getid());
                    }
                    //sweepflat.erase(seg2it);
                    //sweepflatposition.erase(j2->second);
                }
                else if((j->first < M_PI) && (j2->first < M_PI) && (j2->first < j->first)){
                    if(leftmost == false){
                        handleMergeVertex(p, seg2it, lsegit);
                    }
                }
                else if((j->first >= M_PI) && (j2->first < M_PI)){
                    handleRegularLeftVertex(p, seg1it, seg2it);
                    helper[j->second] = make_pair(regular, p.getid());
                }
                else if((j->first < M_PI) && (j2->first >= M_PI)){
                    if(leftmost == false){
                        handleRegularRightVertex(p, lsegit);
                    }
                }
                else {
                    cout << "shouldn't exist situation not noraml point :"
                         << pl.getid() << " : " << p.getid();
                    int k;
                    cin >> k;
                }
            }
        }
        for(auto j = nearSegment.begin(); j != nearSegment.end(); j++){
            if(j->first < M_PI){
                auto it = sweepflatposition[j->second];
                sweepflat.erase(it);
                sweepflatposition.erase(j->second);
                helper.erase(j->second);
            }
        }
        if(i == allPoints.begin()){
            break;
        }
        i--;
    }
    pl = Data::planars[pl.getid()];
}


void Triangulation::handleStartVertex(Point& p, set<Segment>::iterator& ei){
    helper[ei->getid()] = make_pair(start, p.getid());
}

void Triangulation::handleEndVertex(Point& p, set<Segment>::iterator& ei){
    PointType t = helper[ei->getid()].first;
    if(t == merge){
        Point p2 = Data::points[helper[ei->getid()].second];
        set<int> inPlanar;
        inPlanar.insert(pl.getid());
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum, inPlanar);
        Data::segmentsnum++;
        set<int> plexistsegments = pl.getexistsegments();
        plexistsegments.insert(newseg.getid());
        pl.setexistsegments(plexistsegments);
    }
}

void Triangulation::handleSplitVertex(Point& p, set<Segment>::iterator& ei,
                                      set<Segment>::iterator& ej){
    Point p2 = Data::points[helper[ei->getid()].second];
    set<int> inPlanar;
    inPlanar.insert(pl.getid());
    Segment newseg(p.getid(), p2.getid(), Data::segmentsnum, inPlanar);
    Data::segmentsnum++;
    set<int> plexistsegments = pl.getexistsegments();
    plexistsegments.insert(newseg.getid());
    pl.setexistsegments(plexistsegments);
    helper[ej->getid()] = make_pair(split, p.getid());
    helper[ei->getid()] = make_pair(split, p.getid());
}

void Triangulation::handleMergeVertex(Point& p, set<Segment>::iterator& ei,
                                      set<Segment>::iterator& ej){
    PointType ti = helper[ei->getid()].first,
        tj = helper[ej->getid()].first;
    set<int> plexistsegments = pl.getexistsegments();
    set<int> inPlanar;
    inPlanar.insert(pl.getid());
    if(ti == merge){
        Point p2 = Data::points[helper[ei->getid()].second];
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum, inPlanar);
        Data::segmentsnum++;
        //set<int> plexistsegments = pl.getexistsegments();
        plexistsegments.insert(newseg.getid());
        //pl.setexistsegments(plexistsegments);
    }
    if(tj == merge){
        Point p2 = Data::points[helper[ej->getid()].second];
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum, inPlanar);
        Data::segmentsnum++;
        //set<int> plexistsegments = pl.getexistsegments();
        plexistsegments.insert(newseg.getid());
        //pl.setexistsegments(plexistsegments);
    }
    pl.setexistsegments(plexistsegments);
    helper[ej->getid()] = make_pair(split, p.getid());
}

void Triangulation::handleRegularLeftVertex(Point& p, set<Segment>::iterator& ei1,
                                            set<Segment>::iterator& ei2){
    PointType t = helper[ei2->getid()].first;
    if(t == merge){
        Point p2 = Data::points[helper[ei2->getid()].second];
        set<int> inPlanar;
        inPlanar.insert(pl.getid());
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum, inPlanar);
        Data::segmentsnum++;
        set<int> plexistsegments = pl.getexistsegments();
        plexistsegments.insert(newseg.getid());
        pl.setexistsegments(plexistsegments);
    }
    helper[ei1->getid()] = make_pair(regular, p.getid());
}

void Triangulation::handleRegularRightVertex(Point& p, set<Segment>::iterator& ej){
    PointType t = helper[ej->getid()].first;
    if(t == merge){
        Point p2 = Data::points[helper[ej->getid()].second];
        set<int> inPlanar;
        inPlanar.insert(pl.getid());
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum, inPlanar);
        Data::segmentsnum++;
        set<int> plexistsegments = pl.getexistsegments();
        plexistsegments.insert(newseg.getid());
        pl.setexistsegments(plexistsegments);
    }
}


vector<Planar> Triangulation::generatorPolygen(){
    map<Point, set<int>> directEdge;
    Segment triangleEdge0 = Data::segments[pl.getsegments()[0]],
        triangleEdge1 = Data::segments[pl.getsegments()[1]],
        triangleEdge2 = Data::segments[pl.getsegments()[2]];
    for(auto i = pl.getexistsegments().begin(); i != pl.getexistsegments().end(); i++){
        Segment seg = Data::segments[*i];
        Point segp0 = Data::points[seg[0]],
            segp1 = Data::points[seg[1]];
        Direction segdi = segp1 - segp0;
        if(triangleEdge0.ifoverlapSegment(seg)){
            if(triangleEdge0.getdirect().dot(segdi) > 0){
                directEdge[segp0].insert(seg.getid());
            }
            else {
                directEdge[segp1].insert(seg.getid());
            }
        }
        else if(triangleEdge1.ifoverlapSegment(seg)){
            if(triangleEdge1.getdirect().dot(segdi) > 0){
                directEdge[segp0].insert(seg.getid());
            }
            else {
                directEdge[segp1].insert(seg.getid());
            }
        }
        else if(triangleEdge2.ifoverlapSegment(seg)){
            if(triangleEdge2.getdirect().dot(segdi) > 0){
                directEdge[segp0].insert(seg.getid());
            }
            else {
                directEdge[segp1].insert(seg.getid());
            }
        }
        else{
            directEdge[segp0].insert(seg.getid());
            directEdge[segp1].insert(seg.getid());
        }
    }
    set<Point> routeps;
    set<int> routesegs;
    vector<Planar> YMonotones;
    Point routep0, routep1;
    Segment routeseg;
    while(1){
        if(routeps.empty()){
            if(directEdge.empty()){
                break;
            }
            else {
                auto it = directEdge.begin();
                auto itsecond = (it->second).begin();
                routep0 = it->first;
                routeps.insert(routep0);
                routeseg = Data::segments[*itsecond];
                //(it->second).erase(itsecond);
                //if((it->second).empty()){
                //    directEdge.erase(it);
                //}
                routesegs.insert(routeseg.getid());
            }
        }
        //routep1 = Data::points[routeseg[1]];
        set<int> nextsegs = directEdge[routep1];
        double smallangle = 2 * M_PI + 1;
        int nextseg = -1;
        Segment seg;
        Point segp0, segp1;
        for(auto i = nextsegs.begin(); i != nextsegs.end(); i++){
            seg = Data::segments[*i];
            //segp0 = Data::points[seg[0]];
            //segp1 = Data::points[seg[1]];
            if(seg[1] == routep1.getid()){
                segp0 = Data::points[seg[1]];
                segp1 = Data::points[seg[0]];
            }
            else{
                segp0 = Data::points[seg[0]];
                segp1 = Data::points[seg[1]];
            }
            double angle = (segp1 - segp0).angle(routep0 - routep1, pl.getnormaldirect());
            if(angle < smallangle){
                smallangle = angle;
                nextseg = seg.getid();
            }
        }
        routeseg = Data::segments[nextseg];
        routep0 = routep1;
        routeps.insert(routep0);
        routesegs.insert(nextseg);
        routep1 = segp1;
        if(routeps.find(routep1) != routeps.end()){
            
        }
    }
}
