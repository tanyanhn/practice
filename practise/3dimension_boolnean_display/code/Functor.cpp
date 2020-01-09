#include"Functor.h"
#include"Data.h"
#include<vector>

using namespace std;


bool FaceContainFace::operator()(const Face& f1, const Face f2){
    vector<int> f2Pls = f2.getplanars();
    Planar f2Pl = Data::planars[f2Pls[0]];
    YinsetContainTriangle functor;
    vector<int> v; v.push_back(f1.getid());
    Yinset yinf1(v);
    return bool functor(yinf1, f2Pl);
}


bool YinsetContainTriangle::operator()(const Yinset& yinset, const Planar& triangle){
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
    
}