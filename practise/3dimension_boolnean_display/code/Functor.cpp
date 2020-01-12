#include"Functor.h"
#include"Data.h"
#include"Tol.h"
#include<vector>
#include<set>
#include<map>
#include<math.h>
#include<iostream>

using namespace std;


bool FaceContainFace::operator()(const Face& f1, const Face f2){
    vector<int> f2Pls = f2.getplanars();
    Planar f2Pl = Data::planars[f2Pls[0]];
    YinsetContainTriangle functor;
    vector<int> v; v.push_back(f1.getid());
    Yinset yinf1(v);
    return bool functor(yinf1, f2Pl);
}


bool YinsetContainTriangle::operator()(const Yinset& yinset, const Planar& triangle, int overlaptriangle = AddOverlap){
    Point p0 = Data::points[triangle.getpoints().[0]],
        p1 = Data::points[triangle.getpoints().[1]],
        p2 = Data::points[triangle.getpoints().[2]];
    Point p((p0[0] + p1[0] + p2[0]) / 3,
            (p0[1] + p1[1] + p2[1]) / 3,
            (p0[2] + p1[2] + p2[2]) / 3,
            Data::pointsnum);
    Data::points[Data::pointsnum] = p;
    Data::pointsnum++;
    Point farpoint = Data::farpoint;
    Segment striaghtLine(p.getid(), fatpoint.getid(), Data::segmentsnum);
    Data::segments[Data::segmentsnum] = striaghtLine;
    Data::segmentsnum++;
    Point intersectPoint;
    vector<Planar> intersectPlanar;
    for(auto i = yinset.getfaces.begin(), i != yinset.getfaces().end(), i++){
        for(auto j = Data::faces[*i].getplanars().begin(),
                j != Data::faces[*i].getplanars().end(), j++){
            Planar pl = Data::planars[*j];
            if(pl.ifcontainPlanar(triangle)){
                if(overlaptriangle == AddOverlap){
                    if(triangle.getnormaldirect().dot(pl.getnormaldirect()) < -Tol::t)
                        return true;
                    else if(triangle.getnormaldirect().dot(pl.getnormaldirect()) > Tol::t)
                        return false;
                    else {
                        cout << "YinsetContainTriangle wrong in overlaptriangle == AddOverlap : "
                             << triangle.getid() << " : " << pl.getid();
                        int i;
                        cin >> i;
                    }
                }
                else if(overlaptriangle == notAddOverlap){
                    return false;
                }
                else {
                    cout << "YinsetContainTriangle wrong in overlaptriangle : "
                         << triangle.getid() << " : " << pl.getid();
                    int i;
                    cin >> i;
                }
            }
            Segment seg0 = Data::segments[pl.getsegments().[0]],
                seg1 = Data::segments[pl.getsegments().[1]],
                seg2 = Data::segments[pl.getsegments().[2]];
            Point p0 = Data::points[pl.getpoints().[0]],
                p1 = Data::points[pl.getpoints().[1]],
                p2 = Data::points[pl.getpoints().[2]];
            // int t = 0;
            bool ifcloser = false;
            bool ifequal = false;
            bool ifintersectEdge = false;
            Point interP;
            if(striaghtLine.ifcontainPoint(p0)){
                ifintersectEdge = true;
                interP = p0;
                if(interP == intersectPoint){
                    ifequal = true;
                }
                if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                    ifcloser = true;
                    intersectPoint = interP;
                }
            }
            if(striaghtLine.ifcontainPoint(p1)){
                ifintersectEdge = true;
                interP = p1;
                if(interP == intersectPoint){
                    ifequal = true;
                }
                if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                    ifcloser = true;
                    intersectPoint = interP;
                }
            }
            if(striaghtLine.ifcontainPoint(p2)){
                ifintersectEdge = true;
                interP = p2;
                if(interP == intersectPoint){
                    ifequal = true;
                }
                if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                    ifcloser = true;
                    intersectPoint = interP;
                }
            }
            if(ifintersectEdge == false){
                if(striaghtLine.ifintersectionSegment(seg0)){
                    ifintersectEdge = true;
                    // t++;
                    interP = striaghtLine.intersectionSegment(seg0);
                    if(interP == intersectPoint){
                        ifequal = true;
                    }
                    if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                        ifcloser = true;
                        intersectPoint = interP;
                    }
                }
                if(striaghtLine.ifintersectionSegment(seg1)){
                    ifintersectEdge = true;
                    // t++;
                    interP = striaghtLine.intersectionSegment(seg1);
                    if(interP == intersectPoint){
                        ifequal = true;
                    }
                    if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                        ifcloser = true;
                        intersectPoint = interP;
                    }
                }
                if(striaghtLine.ifintersectionSegment(seg2)){
                    ifintersectEdge = true;
                    // t++;
                    interP = striaghtLine.intersectionSegment(seg1);
                    if(interP == intersectPoint){
                        ifequal = true;
                    }
                    if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                        ifcloser = true;
                        intersectPoint = interP;
                    }
                }
            }
            if(ifintersectEdge){
                if(ifcloser){
                    intersectPlanar.clear();
                    intersectPlanar.push_back(pl);
                }
                else if(ifequal) {
                    intersectPlanar.push_back(pl);
                }
            }
            else {
                if(pl.ifintersectionLine(striaghtLine)){
                    interP = pl.intersectionSegment(striaghtLine);
                    if((interP - p).norm() < (intersectPoint - p).norm() - Tol::t){
                        intersectPoint = interP;
                        intersectPlanar.clear();
                        intersectPlanar.push_back(pl);
                    }
                }
            }
        }
    }
    if(intersectPlanar.empty()){
        return yinset.gettype();
    }
    else if(intersecPlanar.size() == 1){
        Planar interpl = intersectPlanar[0];
        Direction d = intersectPoint - p;
        double dou = d.dot(interpl.getnormaldirect());
        if(dou > 0){
            return 1;
        }
        else if(dou < 0){
            return 0;
        }
        else {
            cout << "YinsetContainTriangle:: intersectPlanar.size() == 1 wrong :"
                 << interpl.getid() <<" : ";
            int i;
            cin >> i;
        }
    }
    else {
        Direction d = intersectPoint - p;
        double angle = M_PI;
        Planar closePl;
        for(auto i = intersectPlanar.begin(), i != intersectPlanar.end(), i++){
            Planar Pl = *i;
            Segment seg,
                seg0 = Data::segments[Pl.getsegments[0]],
                seg1 = Data::segments[Pl.getsegments[1]],
                seg2 = Data::segments[Pl.getsegments[2]];
            if(seg0.ifcontainPoint(intersectPoint)){
                seg = seg0;
            }
            if(seg1.ifcontainPoint(intersectPoint)){
                seg = seg1;
            }
            if(seg2.ifcontainPoint(intersectPoint)){
                seg = seg2;
            }
            Direction d1;
            if(find(seg.getinPlanar01().begin(), seg.getinPlanar01().end(), Pl.getid())){
                d1 = Data::points[seg[0]] - Data::points[seg[1]];
            }
            else if(find(seg.getinPlanar10().begin(), seg.getinPlanar10().end(), Pl.getid())){
                d1 = Data::points[seg[1]] - Data::points[seg[0]];
            }
            Direction normal = d.cross(d1);
            Flat flat(intersectPoint, normal);
            double a = flat.angleBetweenFlats(Pl, d1);
            if(a >= M_PI)
                a = 2 * M_PI - a;
            if(a < angle){
                angle = a;
                closePl = Pl;
            }
        }
        if(d.dot(closePl.getnormaldirect()) > 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}



vector<int> FindNearTriangle::operator()(const Planar& triangle){
    Segment seg0 = Data::segments[triangle.getsegments().[0]],
        seg1 = Data::segments[triangle.getsegments().[1]],
        seg2 = Data::segments[triangle.getsegments().[2]];
    vector<Segment> vSeg;
    vector<int> anwser;
    vSeg.push_back(seg0); vSeg.push_back(seg1); vSeg.push_back(seg2);
    for(auto i = vSeg.begin(), i != vSeg.end(), i++){
        double angle = 2 * M_PI + 1;
        if(find(*i.getinPlanar01().begin(), *i.getinPlanar01().end(), triangle.getid())){
            Direction d = Data::points[i->[1]] - Data::points[i->[0]];
            int k = -1;
            for(auto j = *i.getinPlanar10().begin(), j != *i.getinPlanar10().end(), j++){
                double a = triangle.angleBetweenFlats(Data::planars[*j], d);
                if(a < angle){
                    angle = a;
                    k = *j;
                }
            }
            if(k = -1){
                cout << "FindNearTriangle wrong   k = -1: " << triangle.getid();
                int i;
                cin >> i;
            }
            anwser.push_back(k);
        }
        else if(find(*i.getinPlanar10().begin(), *i.getinPlanar10().end(), triangle.getid())){
            Direction d = Data::points[i->[0]] - Data::points[i->[1]];
            int k = -1;
            for(auto j = *i.getinPlanar01().begin(), j != *i.getinPlanar01().end(), j++){
                double a = triangle.angleBetweenFlats(Data::planars[*j], d);
                if(a < angle){
                    angle = a;
                    k = *j;
                }
            }
            if(k = -1){
                cout << "FindNearTriangle wrong : " << triangle.getid();
                int i;
                cin >> i;
            }
            anwser.push_back(k);
        }
        else {
            cout << "FindNearTriangle wrong   else: " << triangle.getid();
            int i;
            cin >> i;
        }
    }
    return anwser;
}


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
    bool tr1notintersect = false, tr1intersectPoint = false, tr1intersectSegment = false,
        tr2notintersect = false, tr2intersectPoint = false, tr2intersectSegment = false;
    if(tr1.Flat::ifcontainPoint(p0) &&
       tr1.Flat::ifcontainPoint(p1) &&
       tr1.Flat::ifcontainPoint(p2)) {
        /* if(tr1.ifcontainSegment(seg0)){
            for(auto i = existsegments.begin(), i != existsegments.end(0), i++){
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
    if(tr1segp0 > tr1segp1){
        Point temp = tr1segp0;
        tr1segp0 = tr1segp1;
        tr1segp1 = temp;
    }
    return Segment(tr1segp0.getid(), tr1segp1.getid());
}