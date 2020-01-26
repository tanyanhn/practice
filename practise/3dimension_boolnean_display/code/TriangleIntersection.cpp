#include"TriangleIntersection.h"
#include"Data.h"
#include"Tol.h"
#include<vector>
#include<set>
#include<map>
#include<math.h>
#include<utility>
#include<iostream>
#include<algorithm>

using namespace std;


void TriangleIntersection::operator()(Planar& tr1, Planar& tr2){
    Point tr2p0 = Data::points[tr2.getpoints()[0]],
        tr2p1 = Data::points[tr2.getpoints()[1]],
        tr2p2 = Data::points[tr2.getpoints()[2]],
        tr1p0 = Data::points[tr1.getpoints()[0]],
        tr1p1 = Data::points[tr1.getpoints()[1]],
        tr1p2 = Data::points[tr1.getpoints()[2]];
    Segment tr2seg0 = Data::segments[tr2.getsegments()[0]],
        tr2seg1 = Data::segments[tr2.getsegments()[1]],
        tr2seg2 = Data::segments[tr2.getsegments()[2]],
        tr1seg0 = Data::segments[tr1.getsegments()[0]],
        tr1seg1 = Data::segments[tr1.getsegments()[1]],
        tr1seg2 = Data::segments[tr1.getsegments()[2]],
        tr1IntersectSegment,
        tr2IntersectSegment;
    set<int> tr1existsegments = tr1.getexistsegments();
    set<int> tr2existsegments = tr2.getexistsegments();
    set<int> tr1existpoints = tr1.getexistpoints();
    set<int> tr2existpoints = tr2.getexistpoints();
    bool tr1notintersect = false, tr1intersectPoint = false, tr1intersectSegment = false,
        tr2notintersect = false, tr2intersectPoint = false, tr2intersectSegment = false;
    if(tr1.Flat::ifcontainPoint(p0) &&
       tr1.Flat::ifcontainPoint(p1) &&
       tr1.Flat::ifcontainPoint(p2)) {
        /* if(tr1.ifcontainSegment(seg0)){
           for(auto i = existsegments.begin(); i != existsegments.end(0); i++){
           Segment seg = Data::segments[*i];
           map<Point, vector<Segment>> intersect;
           if(seg0.ifintersectionSegment(seg)){
           }
           }
           }*/
        tr2notintersect = true;
        tr1notintersect = true;
    }
    else if(tr1.Flat::ifintersectionFlat(tr2) == false){
        tr2notintersect = true;
        tr1notintersect = true;
    }
    else {
        Line l = tr1.Flat::intersectionFlat(tr2);
        tr1IntersectSegment = PlanarIntersectLine(tr1, l, tr1notintersect, tr1intersectPoint, tr1intersectSegment);
        tr2IntersectSegment = PlanarIntersectLine(tr2, l, tr2notintersect, tr2intersectPoint, tr2intersectSegment);
    }
    if(tr1notintersect || tr2notintersect){
        return;
    }
    else if(tr1intersectPoint && tr2intersectPoint){
        return;
        /*
          Point p1 = Data::points[(tr1IntersectSegment[0] == -1 ? tr1IntersectSegment[1] : tr1IntersectSegment[0])];
          Point p2 = Data::points[(tr2IntersectSegment[0] == -1 ? tr2IntersectSegment[1] : tr2IntersectSegment[0])];
        */
    }
    else if(tr1intersectPoint){
        Point p1 = Data::points[(tr1IntersectSegment[0] == -1) ? tr1IntersectSegment[1] : tr1IntersectSegment[0]];
        if(tr2IntersectSegment.ifcontainPoint(p1)){
            Data::pastpoints[p1].insert(tr2.getid());
            /*
            bool find = false;
            //p1.setid(Data::pointsnum);
            //p1.setinSegment(set<int>());
            //Data::pointsnum++;
            //Data::existpoints.insert(p1.getid());
            for(auto i = tr2existpoints.begin(); i != tr2existpoints.end(); i++){
                if(p1 == Data::points[*i])
                    find = true;
            }
            if(find == false){
                //p1.setid(Data::pointsnum);
                //Data::points[Data::pointsnum] = p1;
                //Data::existpoints.push_back(Data::pointsnum);
                //Data::pointsnum++;
                p1.setid(Data::pointsnum);
                p1.setinSegment(set<int>());
                Data::pointsnum++;
                Data::existpoints.insert(p1.getid());
                tr2existpoints.insert(p1.getid());
            }
            tr2.setexistpoints(tr2existpoints);
            */
            return;
        }
        else {
            return;
        }
    }
    else if(tr2intersectPoint){
        Point p2 = Data::points[(tr2IntersectSegment[0] == -1) ? tr2IntersectSegment[1] : tr2IntersectSegment[0]];
        if(tr1IntersectSegment.ifcontainPoint(p2)){
            Data::pastpoints[p2].insert(tr1.getid());
            /*
            bool find = false;
            //Data::existpoints.insert(p2.getid());
            for(auto i = tr1existpoints.begin(); i != tr1existpoints.end(); i++){
                if(p2 == Data::points[*i])
                    find = true;
            }
            if(find == false){
                //p2.setid(Data::pointsnum);
                //Data::points[Data::pointsnum] = p2;
                //Data::existpoints.push_back(Data::pointsnum);
                //Data::pointsnum++;
                p1.setid(Data::pointsnum);
                p1.setinSegment(set<int>());
                Data::pointsnum++;
                Data::existpoints.insert(p1.getid());
                tr1existpoints.insert(p2.getid());
            }
            tr1.setexistpoints(tr1existpoints);
            */
            return;
        }
        else {
            return;
        }
    }
    else {
        if(tr1IntersectSegment.ifoverlapSegment(tr2IntersectSegment) == false){
            return;
        }
        else {
            Segment intersectseg = tr1IntersectSegment.overlapSegment(tr2IntersectSegment);
            if(Data::points[intersectseg[0]] == Data::points[intersectseg[1]]){
                Point p = Data::points[intersectseg[0]];
                Data::pastpoints[p].insert(tr1.getid());
                Data::pastpoints[p].insert(tr2.getid());
                /*
                Data::existpoints.insert(intersectseg[0]);
                tr1existpoints.insert(intersectseg[0]);
                tr2existpoints.insert(intersectseg[0]);
                tr1.setexistpoints(tr1existpoints);
                tr2.setexistpoints(tr2existpoints);
                */
                return;
            }
            Data::existpoints.insert(intersectseg[0]);
            Data::existpoints.insert(intersectseg[1]);
            bool findtr1 = false, findtr2 = false;
            int findidtr1 = -1, findidtr2 = -1;
            for(auto i = tr1existsegments.begin(); i != tr1existsegments.end(); i++){
                if(intersectseg == Data::segments[*i]){
                    findtr1 = true;
                    findidtr1 = *i;
                }
            }
            for(auto i = tr2existsegments.begin(); i != tr2existsegments.end(); i++){
                if(intersectseg == Data::segments[*i]){
                    findtr2 = true;
                    findidtr2 = *i;
                }
            }
            if((findtr1 == false) && (findtr2 == false)) {
                set<int> inPlanar = intersectseg.getinPlanar();
                inPlanar.insert(tr1.getid());
                inPlanar.insert(tr2.getid());
                intersectseg.setinPlanar(inPlanar);
                intersectseg.setid(Data::segmentsnum);
                Data::segments[Data::segmentsnum] = intersectseg;
                Data::existsegments.insert(Data::segmentnum);
                Data::segmentsnum++;
                tr1existsegments.insert(intersectseg.getid());
                tr2existsegments.insert(intersectseg.getid());
                tr1.setexistsegments(tr1existsegments);
                tr2.setexistsegments(tr2existsegments);
                return;
            }
            else if((findtr1 == true) && (findtr2 == false)){
                intersectseg = Data::segments[findidtr1];
                set<int> inPlanar = intersectseg.getinPlanar();
                inPlanar.insert(tr1.getid());
                inPlanar.insert(tr2.getid());
                intersectseg.setinPlanar(inPlanar);
                Data::segments[findidtr1] = intersectseg;
                tr1existsegments.insert(intersectseg.getid());
                tr2existsegments.insert(intersectseg.getid());
                tr1.setexistsegments(tr1existsegments);
                tr2.setexistsegments(tr2existsegments);
                return;
            }
            else if((findtr1 == false) && (findtr2 == true)){
                intersectseg = Data::segments[findidtr2];
                set<int> inPlanar = intersectseg.getinPlanar();
                inPlanar.insert(tr1.getid());
                inPlanar.insert(tr2.getid());
                intersectseg.setinPlanar(inPlanar);
                Data::segments[findidtr2] = intersectseg;
                tr1existsegments.insert(intersectseg.getid());
                tr2existsegments.insert(intersectseg.getid());
                tr1.setexistsegments(tr1existsegments);
                tr2.setexistsegments(tr2existsegments);
                return;
            }
            else if(findidtr1 == findidtr2){
                intersectseg = Data::segments[findidtr2];
                set<int> inPlanar = intersectseg.getinPlanar();
                inPlanar.insert(tr1.getid());
                inPlanar.insert(tr2.getid());
                intersectseg.setinPlanar(inPlanar);
                Data::segments[findidtr2] = intersectseg;
                tr1existsegments.insert(intersectseg.getid());
                tr2existsegments.insert(intersectseg.getid());
                tr1.setexistsegments(tr1existsegments);
                tr2.setexistsegments(tr2existsegments);
                return;
            }
            else {
                cout << "Functor.cpp TriangleIntersection:: intersectseg insert findtr1 and findtr2 all true and findid different : " << tr1.getid() << " : " << tr2.getid();
                int i;
                cin >> i;
            }
        }
    }
}


Segment TriangleIntersection::PlanarIntersectLine(const Planar& tr1, const Line& l,
                                                  bool& tr1notintersect, bool& tr1intersectPoint,bool& tr1intersectSegment) {
    Point tr1p0 = Data::points[tr1.getpoints()[0]],
        tr1p1 = Data::points[tr1.getpoints()[1]],
        tr1p2 = Data::points[tr1.getpoints()[2]];
    Segment tr1seg0 = Data::segments[tr1.getsegments()[0]],
        tr1seg1 = Data::segments[tr1.getsegments()[1]],
        tr1seg2 = Data::segments[tr1.getsegments()[2]];
    Point tr1segp0, tr1segp1,
        tr2segp0, tr2segp1;
    if(l.ifcontainPoint(tr1p0)){
        tr1segp0 = tr1p0;
        if(l.ifcontainPoint(tr1p1)){
            tr1segp1 = tr1p1;
            tr1intersectSegment = true;
        }
        else if(l.ifcontainPoint(tr1p2)){
            tr1segp1 = tr1p2;
            tr1intersectSegment = true;
        }
        else {
            if(l.ifintersectionLine(tr1seg1) == false){
                tr1intersectPoint = true;
            }
            else {
                Point p = l.intersectionLine(tr1seg1);
                if(tr1seg1.ifcontainPoint(p) == false){
                    tr1intersectPoint = true;
                }
                else {
                    p.setid(Data::pointsnum);
                    Data::points[Data::pointsnum] = p;
                    Data::pointsnum++;
                    tr1segp1 = p;
                }
            }
        }
    }
    else if(l.ifcontainPoint(tr1p1)){
        tr1segp0 = tr1p1;
        if(l.ifcontainPoint(tr1p0)){
            tr1segp1 = tr1p0;
            tr1intersectSegment = true;
        }
        else if(l.ifcontainPoint(tr1p2)){
            tr1segp1 = tr1p2;
            tr1intersectSegment = true;
        }
        else {
            if(l.ifintersectionLine(tr1seg2) == false){
                tr1intersectPoint = true;
            }
            else {
                Point p = l.intersectionLine(tr1seg2);
                if(tr1seg1.ifcontainPoint(p) == false){
                    tr1intersectPoint = true;
                }
                else {
                    p.setid(Data::pointsnum);
                    Data::points[Data::pointsnum] = p;
                    Data::pointsnum++;
                    tr1segp1 = p;
                }
            }
        }
    }
    else if(l.ifcontainPoint(tr1p2)){
        tr1segp0 = tr1p2;
        if(l.ifcontainPoint(tr1p1)){
            tr1segp1 = tr1p1;
            tr1intersectSegment = true;
        }
        else if(l.ifcontainPoint(tr1p0)){
            tr1segp1 = tr1p0;
            tr1intersectSegment = true;
        }
        else {
            if(l.ifintersectionLine(tr1seg0) == false){
                tr1intersectPoint = true;
            }
            else {
                Point p = l.intersectionLine(tr1seg0);
                if(tr1seg1.ifcontainPoint(p) == false){
                    tr1intersectPoint = true;
                }
                else {
                    p.setid(Data::pointsnum);
                    Data::points[Data::pointsnum] = p;
                    Data::pointsnum++;
                    tr1segp1 = p;
                }
            }
        }
    }
    else {
        bool firstintersect = false;
        if(l.ifintersectionLine(tr1seg0)){
            Point p = l.intersectionLine(tr1seg0);
            if(tr1seg0.ifcontainPoint(p)){
                if(firstintersect == false){
                    firstintersect = true;
                    p.setid(Data::pointsnum);
                    Data::points[Data::pointsnum] = p;
                    Data::pointsnum++;
                    tr1segp0 = p;
                }
                else {
                    p.setid(Data::pointsnum);
                    Data::points[Data::pointsnum] = p;
                    Data::pointsnum++;
                    tr1segp1 = p;
                }
            }
        }
        if(l.ifintersectionLine(tr1seg1)){
            Point p = l.intersectionLine(tr1seg1);
            if(tr1seg1.ifcontainPoint(p)){
                if(firstintersect == false){
                    firstintersect = true;
                    p.setid(Data::pointsnum);
                    Data::points[Data::pointsnum] = p;
                    Data::pointsnum++;
                    tr1segp0 = p;
                }
                else {
                    p.setid(Data::pointsnum);
                    Data::points[Data::pointsnum] = p;
                    Data::pointsnum++;
                    tr1segp1 = p;
                }
            }
        }
        if(l.ifintersectionLine(tr1seg2)){
            Point p = l.intersectionLine(tr1seg2);
            if(tr1seg2.ifcontainPoint(p)){
                if(firstintersect == false){
                    firstintersect = true;
                    p.setid(Data::pointsnum);
                    Data::points[Data::pointsnum] = p;
                    Data::pointsnum++;
                    tr1segp0 = p;
                }
                else {
                    p.setid(Data::pointsnum);
                    Data::points[Data::pointsnum] = p;
                    Data::pointsnum++;
                    tr1segp1 = p;
                }
            }
        }
        if(firstintersect == false){
            tr1notintersect == true;
        }
    }
    /*
    if(tr1segp0 > tr1segp1){
        Point temp = tr1segp0;
        tr1segp0 = tr1segp1;
        tr1segp1 = temp;
    }
    */
    return Segment(tr1segp0.getid(), tr1segp1.getid());
}