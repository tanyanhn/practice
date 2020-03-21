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
    vector<Planar> triangles;
    if(p.getexistsegments().size() == 3){
        triangles.push_back(p);
        return triangles;
    }
    pl = p;
    //Direction outside = p.getnormaldirect();
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
    (*Tol::outside) = sweepline.getdirect().cross(f.getnormaldirect()).unit();
    makeMonotone();
    vector<Planar> yMonotones = generatorPolygen();
    for(auto i = yMonotones.begin(); i != yMonotones.end(); i++){
        TriangulateMonotonePolygon(*i);
    }
    triangles = generatorPolygen();
    for(auto i = triangles.begin(); i != triangles.end(); i++){
        i->setinYinset(pl.getinYinset());
        Planar triangle = *i;
        if(triangle.getexistsegments().size() != 3){
            cout << "trianglulation wrong triangle.id : " << triangle.getid()  << " "
                 << pl.getid();
            int* pi = 0;
            std::cout << *pi;
        }
        else{
            set<int> ssegments = triangle.getexistsegments();
            vector<int> points,
                segments;
            points.resize(3);
            segments.resize(3);
            copy(ssegments.begin(), ssegments.end(), segments.begin());
            Segment seg0 = Data::segments[segments[0]],
                seg1 = Data::segments[segments[1]],
                seg2 = Data::segments[segments[2]];
            for(int k = 0; k < 3; k++){
                set<int> inPlanar = Data::segments[segments[k]].getinPlanar();
                inPlanar.erase(pl.getid());
                inPlanar.insert(triangle.getid());
                Data::segments[segments[k]].setinPlanar(inPlanar);
            }
            if(seg0[0] == seg1[0]){
                points[0] = seg0[1];
                points[1] = seg0[0];
                points[2] = seg1[1];
            }
            else if(seg0[0] == seg1[1]){
                points[0] = seg0[1];
                points[1] = seg0[0];
                points[2] = seg1[0];
            }
            else if(seg0[1] == seg1[0]){
                points[0] = seg0[0];
                points[1] = seg0[1];
                points[2] = seg1[1];
            }
            else if(seg0[1] == seg1[1]){
                points[0] = seg0[0];
                points[1] = seg0[1];
                points[2] = seg1[0];
            }
            triangle.setpoints(points);
            triangle.setsegments(segments);
            if(seg0[0] == points[0]){
                set<int> inPlanar01 = seg0.getinPlanar01();
                inPlanar01.insert(triangle.getid());
                seg0.setinPlanar01(inPlanar01);
            }
            else{
                set<int> inPlanar10 = seg0.getinPlanar10();
                inPlanar10.insert(triangle.getid());
                seg0.setinPlanar10(inPlanar10);
            }
            if(seg1[0] == points[1]){
                set<int> inPlanar01 = seg1.getinPlanar01();
                inPlanar01.insert(triangle.getid());
                seg1.setinPlanar01(inPlanar01);
            }
            else{
                set<int> inPlanar10 = seg1.getinPlanar10();
                inPlanar10.insert(triangle.getid());
                seg1.setinPlanar10(inPlanar10);
            }
            if(seg2[0] == points[2]){
                set<int> inPlanar01 = seg2.getinPlanar01();
                inPlanar01.insert(triangle.getid());
                seg2.setinPlanar01(inPlanar01);
            }
            else{
                set<int> inPlanar10 = seg2.getinPlanar10();
                inPlanar10.insert(triangle.getid());
                seg2.setinPlanar10(inPlanar10);
            }
        }
    }
    sweepflatposition.clear();
    helper.clear();
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
                nearSegment[sweepline.getdirect().angle(segdirect, *Tol::outside)]
                    = seg.getid();
            }
        }
        if(nearSegment.empty()){
            cout << "Triangulation::makeMonotone nearSegment.empty is true : " << pl.getid()
                 << " : " << p.getid();
            int* pi = 0;
            std::cout << *pi;
        }
        bool leftmost = false;
        //set<Segment>::iterator lsegit;
        int lsegid = -1;
        int leftseg = -1;
        double leftsegangle = -1;
        for(auto j = nearSegment.begin(); j != nearSegment.end(); j++){
            if(j->first >= 0 && j->first < M_PI && j->first > leftsegangle){
                leftsegangle = j->first;
                leftseg = j->second;
            }
        }
        set<Segment>::iterator lit;
        int insertid = -1;
        if(leftseg == -1){
            insertid = nearSegment.begin()->second;
            auto it = sweepflat.insert(Data::segments[insertid]).first;
            sweepflatposition[insertid] = it;
            lit = it;
        }
        else {
            lit = sweepflatposition[leftseg];
        }
        //auto lit = sweepflatposition[leftseg];
        if(lit == sweepflat.begin()){
            leftmost = true;
        }
        else{
            --lit;
            //lsegit = lit;
            lsegid = lit->getid();
        }
        if(leftseg == -1){
            auto it = sweepflatposition[insertid];
            sweepflat.erase(it);
            sweepflatposition.erase(insertid);
        }
        if(nearSegment.size() == 1){
            auto j = nearSegment.begin();
            //set<Segment>::iterator segit = sweepflat.insert(Data::segments[j->second]).first;
            //sweepflatposition[j->second] = segit;
            int segid = j->second;
            if(!(j->first >= M_PI)){
                if(leftmost == false){
                    handleSplitVertex(p, segid, lsegid);
                }
                else{
                    cout << "shouldn't exist situation segment exist outside triangle :"
                         << pl.getid() << " : " << p.getid();
                    int* pi = 0;
                    std::cout << *pi;
                }
            }
            else {
                if(leftmost == false){
                    handleMergeVertex(p, segid, lsegid);
                }
                else{
                    cout << "shouldn't exist situation segment exist outside triangle :"
                         << pl.getid() << " : " << p.getid();
                    int* pi = 0;
                    std::cout << *pi;
                }
            }
            if(j->first < M_PI){
                //sweepflatposition.erase(j->second);
                //sweepflat.erase(segit);
                auto segit = sweepflatposition[segid];
                sweepflat.erase(segit);
                sweepflatposition.erase(segid);
                helper.erase(segid);
            }
            else{
                set<Segment>::iterator segit = sweepflat.insert(Data::segments[j->second]).first;
                sweepflatposition[segid] = segit;
                helper[segid] = make_pair(split, p.getid());
            }
        }
        else {
            /*
              for(auto j = nearSegment.begin(); j != nearSegment.end(); j++){
              if(j->first >= M_PI){
              auto it = sweepflat.insert(Data::segments[j->second]).first;
              sweepflatposition[j->second] = it;
              }
              }
            */
            for(auto j = nearSegment.begin(); j != nearSegment.end(); j++){
                //set<Segment>::iterator seg1it, seg2it;
                int seg1id = j->second;
                //seg1it = sweepflatposition[j->second];
                /*
                  if(sweepflatposition.find(j->second) != sweepflat.end()){
                  seg1it = sweepflatposition[j->second];
                  }
                  else{
                  seg1it = sweepflat.insert(Data::segments[j->second]);
                  sweepflatposition[j->second] = seg1it;
                  }
                */
                auto j2 = next(j);
                if(j2 == nearSegment.end()){
                    j2 = nearSegment.begin();
                }
                int seg2id = j2->second;
                //seg2it = sweepflatposition[j2->second];
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
                    //handleStartVertex(p, seg1it);
                    handleStartVertex(p, seg1id);
                    //helper[j->second] = make_pair(start, p.getid());
                    //sweepflat.erase(seg2it);
                    //sweepflatposition.erase(j2->second);
                }
                else if((j->first < M_PI) && (j2->first < M_PI) && (j2->first > j->first)){
                    //handleEndVertex(p, seg2it);
                    handleEndVertex(p, seg2id);
                    //sweepflat.erase(seg2it);
                    //sweepflatposition.erase(j2->second);
                    //helper.erase(j2->second);
                }
                else if((j->first > M_PI) && (j2->first >= M_PI) && (j2->first < j->first)){
                    if(leftmost == false){
                        //handleSplitVertex(p, seg1it, lsegit);
                        handleSplitVertex(p, seg1id, lsegid);
                        //helper[j->second] = make_pair(split, p.getid());
                    }
                    //sweepflat.erase(seg2it);
                    //sweepflatposition.erase(j2->second);
                }
                else if((j->first < M_PI) && (j2->first < M_PI) && (j2->first < j->first)){
                    if(leftmost == false){
                        //handleMergeVertex(p, seg2it, lsegit);
                        handleMergeVertex(p, seg2id, lsegid);
                    }
                }
                else if((j->first >= M_PI) && (j2->first < M_PI)){
                    //handleRegularLeftVertex(p, seg1it, seg2it);
                    handleRegularLeftVertex(p, seg1id, seg2id);
                    helper[j->second] = make_pair(regular, p.getid());
                }
                else if((j->first < M_PI) && (j2->first >= M_PI)){
                    if(leftmost == false){
                        //handleRegularRightVertex(p, lsegit);
                        handleRegularRightVertex(p, lsegid);
                    }
                }
                else {
                    cout << "shouldn't exist situation not noraml point :"
                         << pl.getid() << " : " << p.getid();
                    int* pi = 0;
                    std::cout << *pi;
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
        for(auto j = nearSegment.begin(); j != nearSegment.end(); j++){
            if(j->first >= M_PI){
                auto it = sweepflat.insert(Data::segments[j->second]).first;
                sweepflatposition[j->second] = it;
            }
        }
        if(i == allPoints.begin()){
            break;
        }
        i--;
    }
    pl = Data::planars[pl.getid()];
}


void Triangulation::handleStartVertex(Point& p, int ei){
    //helper[ei->getid()] = make_pair(start, p.getid());
    helper[ei] = make_pair(start, p.getid());
}

void Triangulation::handleEndVertex(Point& p, //set<Segment>::iterator&
                                    int ei){
    //PointType t = helper[ei->getid()].first;
    PointType t = helper[ei].first;
    if(t == merge){
        //Point p2 = Data::points[helper[ei->getid()].second];
        Point p2 = Data::points[helper[ei].second];
        set<int> inPlanar;
        inPlanar.insert(pl.getid());
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum++, inPlanar);
        //Data::segmentsnum++;
        set<int> plexistsegments = pl.getexistsegments();
        plexistsegments.insert(newseg.getid());
        pl.setexistsegments(plexistsegments);
    }
}

void Triangulation::handleSplitVertex(Point& p, //set<Segment>::iterator&
                                      int ei,
                                      //set<Segment>::iterator&
                                      int ej){
    //Point p2 = Data::points[helper[ei->getid()].second];
    Point p2 = Data::points[helper[ei].second];
    set<int> inPlanar;
    inPlanar.insert(pl.getid());
    Segment newseg(p.getid(), p2.getid(), Data::segmentsnum++, inPlanar);
    //Data::segmentsnum++;
    set<int> plexistsegments = pl.getexistsegments();
    plexistsegments.insert(newseg.getid());
    pl.setexistsegments(plexistsegments);
    //helper[ej->getid()] = make_pair(split, p.getid());
    helper[ej] = make_pair(split, p.getid());
    //helper[ei->getid()] = make_pair(split, p.getid());
    helper[ei] = make_pair(split, p.getid());
}

void Triangulation::handleMergeVertex(Point& p, //set<Segment>::iterator&
                                      int ei,
                                      //set<Segment>::iterator&
                                      int ej){
    //PointType ti = helper[ei->getid()].first, tj = helper[ej->getid()].first;
    PointType ti = helper[ei].first, tj = helper[ej].first;
    set<int> plexistsegments = pl.getexistsegments();
    set<int> inPlanar;
    inPlanar.insert(pl.getid());
    if(ti == merge){
        //Point p2 = Data::points[helper[ei->getid()].second];
        Point p2 = Data::points[helper[ei].second];
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum++, inPlanar);
        //Data::segmentsnum++;
        //set<int> plexistsegments = pl.getexistsegments();
        plexistsegments.insert(newseg.getid());
        //pl.setexistsegments(plexistsegments);
    }
    if(tj == merge){
        //Point p2 = Data::points[helper[ej->getid()].second];
        Point p2 = Data::points[helper[ej].second];
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum++, inPlanar);
        //Data::segmentsnum++;
        //set<int> plexistsegments = pl.getexistsegments();
        plexistsegments.insert(newseg.getid());
        //pl.setexistsegments(plexistsegments);
    }
    pl.setexistsegments(plexistsegments);
    //helper[ej->getid()] = make_pair(split, p.getid());
    helper[ej] = make_pair(split, p.getid());
}

void Triangulation::handleRegularLeftVertex(Point& p, //set<Segment>::iterator&
                                            int ei1,
                                            //set<Segment>::iterator&
                                            int ei2){
    //PointType t = helper[ei2->getid()].first;
    PointType t = helper[ei2].first;
    if(t == merge){
        //Point p2 = Data::points[helper[ei2->getid()].second];
        Point p2 = Data::points[helper[ei2].second];
        set<int> inPlanar;
        inPlanar.insert(pl.getid());
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum++, inPlanar);
        //Data::segmentsnum++;
        set<int> plexistsegments = pl.getexistsegments();
        plexistsegments.insert(newseg.getid());
        pl.setexistsegments(plexistsegments);
    }
    //helper[ei1->getid()] = make_pair(regular, p.getid());
    helper[ei1] = make_pair(regular, p.getid());
}

void Triangulation::handleRegularRightVertex(Point& p, //set<Segment>::iterator&
                                             int ej){
    //PointType t = helper[ej->getid()].first;
    PointType t = helper[ej].first;
    if(t == merge){
        //Point p2 = Data::points[helper[ej->getid()].second];
        Point p2 = Data::points[helper[ej].second];
        set<int> inPlanar;
        inPlanar.insert(pl.getid());
        Segment newseg(p.getid(), p2.getid(), Data::segmentsnum++, inPlanar);
        //Data::segmentsnum++;
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
    Point endPoint0 = Data::points[pl.getpoints()[0]],
        endPoint1 = Data::points[pl.getpoints()[1]],
        endPoint2 = Data::points[pl.getpoints()[2]];
    set<int> existsegments = pl.getexistsegments();
    for(auto i = existsegments.begin(); i != existsegments.end(); i++){
        Segment seg = Data::segments[*i];
        Point segp0 = Data::points[seg[0]],
            segp1 = Data::points[seg[1]];
        Direction segdi = segp1 - segp0;
        if(triangleEdge0.ifoverlapSegment(seg)){
            if(segdi.cross(endPoint2 - endPoint1).dot(*Tol::outside) > 0){
                directEdge[segp0].insert(seg.getid());
            }
            else {
                directEdge[segp1].insert(seg.getid());
            }
        }
        else if(triangleEdge1.ifoverlapSegment(seg)){
            if(segdi.cross(endPoint0 - endPoint2).dot(*Tol::outside) > 0){
                directEdge[segp0].insert(seg.getid());
            }
            else {
                directEdge[segp1].insert(seg.getid());
            }
        }
        else if(triangleEdge2.ifoverlapSegment(seg)){
            if(segdi.cross(endPoint1 - endPoint0).dot(*Tol::outside) > 0){
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
    map<Point, int> route;
    map<Point, int> preroute;
    //map<Point, int> routesegs;
    vector<Planar> YMonotones;
    Point routep0, routep1;
    Segment routeseg, nextseg;
    vector<Planar> anwser;
    Planar polygen;
    set<int> existseg;
    vector<int> polygensegments;
    while(1){
        if(route.empty()){
            if(directEdge.empty()){
                break;
            }
            else {
                auto it = directEdge.begin();
                auto itsecond = (it->second).begin();
                routep0 = it->first;
                route.insert(make_pair(routep0, *itsecond));
                routeseg = Data::segments[*itsecond];
                if(routeseg[0] == routep0.getid()){
                    routep1 = Data::points[routeseg[1]];
                }
                else{
                    routep1 = Data::points[routeseg[0]];
                }
                directEdge[routep0].erase(routeseg.getid());
                if(directEdge[routep0].empty()){
                    directEdge.erase(routep0);
                }
                //(it->second).erase(itsecond);
                //if((it->second).empty()){
                //    directEdge.erase(it);
                //}
                //routesegs.insert(routeseg.getid());
            }
        }
        //routep1 = Data::points[routeseg[1]];
        set<int> nextsegs = directEdge[routep1];
        double smallangle = 2 * M_PI + 1;
        nextseg = routeseg;
        //int nextseg = -1;
        //Segment seg;
        //Point segp0, segp1;
        for(auto i = nextsegs.begin(); i != nextsegs.end(); i++){
            if(*i == routeseg.getid()){
                continue;
            }
            Segment seg = Data::segments[*i];
            Point segp0, segp1;
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
            double angle = (segp1 - segp0).angle(routep0 - routep1, *Tol::outside);
            if(angle < smallangle){
                smallangle = angle;
                nextseg = seg;
            }
        }
        preroute.insert(make_pair(routep1, routeseg.getid()));
        //routeseg = Data::segments[nextseg];
        //routep0 = routep1;
        route.insert(make_pair(routep1, nextseg.getid()));
        //routesegs.insert(nextseg);
        //routep1 = segp1;
        //Point p = Data::segments[nextseg].[];
        directEdge[routep1].erase(nextseg.getid());
        if(directEdge[routep1].empty()){
            directEdge.erase(routep1);
        }
        int nextp0, nextp1;
        if(nextseg[0] == routep1.getid()){
            nextp0 = nextseg[0];
            nextp1 = nextseg[1];
        }
        else {
            nextp0 = nextseg[1];
            nextp1 = nextseg[0];
        }
        Point p = Data::points[nextp1];
        int route_empty = -1;
        while(route.find(p) != route.end()){
            if(!(p.getid() == nextp1)){
                preroute.erase(p);
            }
            Segment seg = Data::segments[route[p]];
            int p2;
            if(seg[0] == p.getid()){
                p2 = seg[1];
            }
            else {
                p2 = seg[0];
            }
            route.erase(p);
            p = Data::points[p2];
            existseg.insert(seg.getid());
            polygensegments.push_back(seg.getid());
            if(route.find(p) == route.end()){
                polygen.setid(Data::planarsnum++);
                //Data::planarsnum++;
                polygen.setexistsegments(existseg);
                polygen.setsegments(polygensegments);
                existseg.clear();
                polygensegments.clear();
                anwser.push_back(polygen);
                if(preroute.empty() && route.empty()){
                    route_empty = 1;
                }
                else {
                    nextseg = Data::segments[preroute[Data::points[nextp1]]];
                    if(nextseg[0] == nextp1){
                        nextp0 = nextseg[1];
                    }
                    else if(nextseg[1] == nextp1){
                        nextp0 = nextseg[0];
                    }
                    //nextseg = routeseg.getid();
                }
                break;
            }
        }
        //if(ifbreak == 1){
        //    break;
        //}
        if(route_empty == -1){
            routep0 = Data::points[nextp0];
            routep1 = Data::points[nextp1];
            routeseg = nextseg;
        }
    }
    return anwser;
}


void Triangulation::TriangulateMonotonePolygon(Planar& planar){
    map<Point, pair<int,int>> nearPoint;
    set<int> existsegment = pl.getexistsegments(),
        planarexistsegment = planar.getexistsegments();
    vector<int> planarsegments = planar.getsegments();
    for(auto i = planarsegments.begin(); i != planarsegments.end(); i++){
        auto j = next(i);
        if(j == planarsegments.end()){
            j = planarsegments.begin();
        }
        Segment seg0 = Data::segments[*i],
            seg1 = Data::segments[*j];
        int p0 = seg0[0],
            p1 = seg0[1],
            p2;
        if(seg1[0] == p0){
            p0 = p1;
            p1 = seg1[0];
            p2 = seg1[1];
        }
        else if(seg1[1] == p0){
            p0 = p1;
            p1 = seg1[1];
            p2 = seg1[0];
        }
        else if(seg1[0] == p1){
            p2 = seg1[1];
        }
        else if(seg1[1] == p1){
            p2 = seg1[0];
        }
        else {
            p2 = -2;
            cout << "void Triangulation::TriangulateMonotonePolygon(Planar& planar) wrong" <<endl;
            int* p = 0;
            *p = 0;
        }
        auto vp = nearPoint[Data::points[p1]];
        vp.first = p0;
        vp.second = p2;
        nearPoint[Data::points[p1]] = vp;
    }
    stack<Point> s;
    auto it = nearPoint.end();
    it--;
    s.push(it->first);
    it--;
    s.push(it->first);
    while(1){
        if(it == nearPoint.begin()){
            break;
        }
        it--;
        Point p = it->first;
        Point topp = s.top();
        auto nearp = nearPoint[p];
        if((nearp.first == topp.getid()) || (nearp.second == topp.getid())){
            Point p1 = s.top();
            s.pop();
            Point p2 = s.top();
            s.pop();
            while(1){
                char side = 'n';
                pair<int, int> prevnext = nearPoint[p];
                if(prevnext.first == p1.getid()){
                    side = 'l';
                }
                else if(prevnext.second == p1.getid()){
                    side = 'r';
                }
                if(((p2 - p1).angle(p - p1, *Tol::outside) >= M_PI && side == 'r') ||
                   ((p2 - p1).angle(p - p1, *Tol::outside) <= M_PI && side == 'l')){
                    break;
                }
                if(nearPoint[p].first != p2.getid() && nearPoint[p].second != p2.getid()){
                    Segment seg(p.getid(), p2.getid(), Data::segmentsnum++);
                    //Data::pointsnum++;
                    existsegment.insert(seg.getid());
                    if(nearPoint[p].first == p1.getid()){
                        nearPoint[p].first = p2.getid();
                    }
                    else if(nearPoint[p].second == p1.getid()){
                        nearPoint[p].second = p2.getid();
                    }
                }
                p1 = p2;
                if(s.empty()){
                    break;
                }
                p2 = s.top();
                s.pop();
            }
            if(p1 == p2){
                s.push(p1);
                s.push(p);
            }
            else{
                s.push(p2);
                s.push(p1);
                s.push(p);
            }
        }
        else{
            Point p2 = s.top(), p1;
            while(1){
                p1 = s.top();
                s.pop();
                if(s.empty()){
                    break;
                }
                if(nearPoint[p].first != p1.getid() && nearPoint[p].second != p1.getid()){
                    Segment seg(p.getid(), p1.getid(), Data::segmentsnum++);
                    //Data::pointsnum++;
                    existsegment.insert(seg.getid());
                }
            }
            if(nearPoint[p].first == p1.getid()){
                nearPoint[p].first = p2.getid();
            }
            else if(nearPoint[p].second == p1.getid()){
                nearPoint[p].second = p2.getid();
            }
            s.push(p2);
            s.push(p);
        }
    }
    pl.setexistsegments(existsegment);
}


/*

vector<Planar> Triangulation::dealexistpoint(vector<Planar>& vpl){
    set<int> existpoints = pl.getexistpoints();
    set<int> existsegments = pl.getexistsegments();
    map<int, set<Point>> segmentcontainPoint;
    for(auto i = existpoints.begin(); i != existpoints.end(); i++){
        Point p = Data::points[*i];
        for(auto j = vpl.begin(); j != vpl.end(); j++){
            Planar pl = *j;
            if(pl.ifcontainPoint(p) == true){
                vector<int> points = pl.getpoints(),
                    segments = pl.getsegments();
                Point p0 = Data::points[points[0]],
                    p1 = Data::points[points[1]],
                    p2 = Data::points[points[2]];
                Segment seg0 = Data::segments[segments[0]],
                    seg1 = Data::segments[segments[1]],
                    seg2 = Data::segments[segments[2]];
                if(p == p0){}
                else if(p == p1){}
                else if(p == p2){}
                else if(seg0.ifcontainPoint(p) == true){
                    Segment segadd(p.getid(), p2.getid(), Data::segmentsnum++);
                    existsegments.insert(segadd.getid());
                    Data::existsegments.insert(segadd.getid());
                    if(exsitsegments.find(seg0.getid()) != existsegments.end()){
                        segmentcontainPoint[seg0.getid()].insert(p);
                    }
                }
                else if(seg1.ifcontainPoint(p) == true){
                    Segment segadd(p.getid(), p0.getid(), Data::segmentsnum++);
                    existsegments.insert(segadd.getid());
                    Data::existsegments.insert(segadd.getid());
                    if(exsitsegments.find(seg1.getid()) != existsegments.end()){
                        segmentcontainPoint[seg1.getid()].insert(p);
                    }
                }
                else if(seg0.ifcontainPoint(p) == true){
                    Segment segadd(p.getid(), p1.getid(), Data::segmentsnum++);
                    existsegments.insert(segadd.getid());
                    Data::existsegments.insert(segadd.getid());
                    if(exsitsegments.find(seg2.getid()) != existsegments.end()){
                        segmentcontainPoint[seg2.getid()].insert(p);
                    }
                }
                else {
                    Segment segadd0(p.getid(), p0.getid(), Data::segmentsnum++),
                        segadd1(p.getid(), p1.getid(), Data::segmentsnum++),
                        segadd2(p.getid(), p2.getid(), Data::segmentsnum++);
                }
            }
        }
    }
}
*/