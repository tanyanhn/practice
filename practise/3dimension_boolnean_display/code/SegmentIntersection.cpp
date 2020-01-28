#include"SegmentIntersection.h"
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



void SegmentIntersection::operator()(Planar& pl){
    set<int> existsegments = pl.getexistsegments();
    set<Point> allPoint;
    for(auto i = existsegments.begin(); i != existsegments.end(); i++){
        Segment seg = Data::segments[*i];
        Point p0 = Data::points[seg[0]],
            p1 = Data::points[seg[1]];
        set<Point>::iterator it0 = allPoint.find(p0),
            it1 = allPoint.find(p1);
        if(it0 != allPoint.end()){
            Point p = *it0;
            set<int> pinSegment = p.getinSegment(),
                p0inSegment = p0.getinSegment();
            /*
              if(pinSegment.size() < p0inSegment.size()){
              allPoint.erase(it0);
              it0 = allPoint.insert(p0);
              swap(p, p0);
              pinSegment = p.getinSegment();
              p0inSegment = p0.getinSegment();
              }
            */
            for(auto j = p0inSegment.begin(); j != p0inSegment.end(); j++){
                Segment segContainp0 = Data::segments[*j];
                if(segContainp0[0] == p0.getid()){
                    segContainp0.setendpoints(0, p.getid());
                }
                if(segContainp0[1] == p0.getid()){
                    segContainp0.setendpoints(1, p.getid());
                }
                Data::points[p0.getid()].setinSegment(set<int>());
                Data::points[p0.getid()].setinYinset(-2);
                Data::existpoints.erase(p0.getid());
                Data::segments[segContainp0.getid()] = segContainp0;
                //pinSegment.insert(*j);
            }
            //p.setinSegment(pinSegment);
            //Data::points[p.getid()] = p;
        }
        else {
            allPoint.insert(p0);
        }
        if(it1 != allPoint.end()){
            Point p = *it1;
            set<int> pinSegment = p.getinSegment(),
                p1inSegment = p1.getinSegment();
            for(auto j = p1inSegment.begin(); j != p1inSegment.end(); j++){
                Segment segContainp1 = Data::segments[*j];
                if(segContainp1[0] == p1.getid()){
                    segContainp1.setendpoints(0, p.getid());
                }
                if(segContainp1[1] == p1.getid()){
                    segContainp1.setendpoints(1, p.getid());
                }
                Data::points[p1.getid()].setinSegment(set<int>());
                Data::points[p1.getid()].setinYinset(-2);
                Data::existpoints.erase(p1.getid());
                Data::segments[segContainp1.getid()] = segContainp1;
                //pinSegment.insert(*j);
            }
        }
        else {
            allPoint.insert(p1);
        }
    }
    for(auto i = existsegments.begin(); i != existsegments.end(); i++){
        Segment seg = Data::segments[*i];
        set<Point> pinseg;
        for(auto j = allPoint.begin(); j != allPoint.end(); j++){
            if(seg.ifcontainPoint(*j)){
                pinseg.insert(*j);
            }
        }
        if(pinseg.size() > 2){
            set<int> allPlanar = seg.getinPlanar();
            for(auto j = pinseg.begin(); j != (--pinseg.end()); j++){
                Point p0 = *j, p1 = *(++j);
                Segment s(p0.getid(), p1.getid(), Data::segmentsnum,
                          seg.getinPlanar01(), seg.getinPlanar10(), seg.getinYinset());
                Data::segmentsnum++;
                s.setinPlanar(seg.getinPlanar());
                set<int> inSegment;
                inSegment = p0.getinSegment();
                inSegment.erase(seg.getid());
                inSegment.insert(s.getid());
                p0.setinSegment(inSegment);
                inSegment = p1.getinSegment();
                inSegment.erase(seg.getid());
                inSegment.insert(s.getid());
                p1.setinSegment(inSegment);
                Data::existsegments.insert(s.getid());
                for(auto j = allPlanar.begin(); j != allPlanar.end(); j++){
                    Planar pl = Data::planars[*j];
                    set<int> plexistsegment = pl.getexistsegments();
                    plexistsegment.insert(seg.getid());
                    pl.setexistsegments(plexistsegment);
                }
            }
            Data::segments[seg.getid()].setinYinset(-2);
            Data::segments[seg.getid()].setinPlanar(set<int>());
            Data::segments[seg.getid()].setinPlanar01(set<int>());
            Data::segments[seg.getid()].setinPlanar10(set<int>());
            Data::existsegments.erase(seg.getid());
            //set<int> allPlanar = seg.getinPlanar();
            for(auto j = allPlanar.begin(); j != allPlanar.end(); j++){
                Planar pl = Data::planars[*j];
                set<int> plexistsegment = pl.getexistsegments();
                plexistsegment.erase(seg.getid());
                pl.setexistsegments(plexistsegment);
            }
        }
        else if(pinseg.size() == 2){}
        else {
            cout << "SegmentIntersection::operator() pinseg < 2 : "
                 << pl.getid();
            int i;
            cin >> i;
        }
    }
    existsegments = Data::planars[pl.getid()].getexistsegments();
    map<pair<int, int>, Segment> segmentmap;
    map<pair<int, int>, Segment>::iterator it;
    for(auto i = existsegments.begin(); i != existsegments.end(); i++){
        Segment seg = Data::segments[*i];
        it = segmentmap.find(make_pair(seg[0], seg[1]));
        if(it != segmentmap.end()){
            Segment overlapseg = it->second;
            set<int> seginPlanar = seg.getinPlanar(),
                inPlanar = overlapseg.getinPlanar();
            for(auto j = seginPlanar.begin(); j != seginPlanar.end(); j++){
                inPlanar.insert(*j);
            }
            overlapseg.setinPlanar(inPlanar);
            set<int> seginPlanar01 = seg.getinPlanar01(),
                inPlanar01 = overlapseg.getinPlanar01();
            for(auto j = seginPlanar01.begin(); j != seginPlanar01.end(); j++){
                inPlanar01.insert(*j);
            }
            overlapseg.setinPlanar01(inPlanar01);
            set<int> seginPlanar10 = seg.getinPlanar10(),
                inPlanar10 = overlapseg.getinPlanar10();
            for(auto j = seginPlanar10.begin(); j != seginPlanar10.end(); j++){
                inPlanar10.insert(*j);
            }
            overlapseg.setinPlanar10(inPlanar10);
            Data::segments[seg.getid()].setinYinset(-2);
            Data::segments[seg.getid()].setinPlanar(set<int>());
            Data::segments[seg.getid()].setinPlanar01(set<int>());
            Data::segments[seg.getid()].setinPlanar10(set<int>());
            Data::existsegments.erase(seg.getid());
            for(auto j = seginPlanar.begin(); j != seginPlanar.end(); j++){
                Planar pl = Data::planars[*j];
                set<int> plexistsegment = pl.getexistsegments();
                plexistsegment.erase(seg.getid());
                pl.setexistsegments(plexistsegment);
                Data::planars[*j] = pl;
            }
        }
        else {
            segmentmap[make_pair(seg[0], seg[1])] = seg;
        }
    }
}
