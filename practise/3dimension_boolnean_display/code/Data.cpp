#include"Point.h"
#include"Segment.h"
#include"Planar.h"
#include"Face.h"
#include"Yinset.h"
#include"HassNode.h"
#include"FunctorHead.h"
#include<map>
#include<set>
#include<vector>
#include<stack>
using namespace std;



std::set<int> Data::existpoints;
std::set<int> Data::existsegments;
std::set<int> Data::existplanars;
std::set<int> Data::existfaces;
std::map<int, Point> Data::points;
std::map<int, Segment> Data::segments;
std::map<int, Planar> Data::planars;
std::map<int, Face> Data::faces;
std::map<int, Yinset> Data::yinsets;
std::map<Point, set<int>> Data::pastpoints;
int Data::pointsnum = 1;
int Data::segmentsnum = 0;
int Data::planarsnum = 0;
int Data::facesnum = 0;
int Data::yinsetsnum = 0;
Point Data::farpoint = Point(0, 0, 0, 0);


void Data::load(const Yinset& y){
    vector<int> yfaces = y.getfaces();
    for(auto i = yfaces.begin(); i != yfaces.end(); i++){
        existfaces.insert(*i);
        Face f = faces[*i];
        f.setinYinset(y.getid());
        vector<int> fplanars = f.getplanars();
        for(auto j = fplanars.begin(); j != fplanars.end(); j++){
            existplanars.insert(*j);
            Planar pl = planars[*j];
            pl.setinYinset(y.getid());
            pl.setinFace(f.getid());
            vector<int> plpoints = pl.getpoints(),
                plsegments = pl.getsegments();
            set<int> existseg;
            vector<Point> p(3);
            vector<Segment> seg(3);
            for(int k = 0; k < 3; k++){
                existsegments.insert(plsegments[k]);
                existpoints.insert(plpoints[k]);
                existseg.insert(plsegments[k]);
                p[k] = points[plpoints[k]];
                p[k].setinYinset(y.getid());
                seg[k] = segments[plsegments[k]];
                seg[k].setinYinset(y.getid());
                set<int> inPlanar = seg[k].getinPlanar();
                inPlanar.insert(pl.getid());
                seg[k].setinPlanar(inPlanar);
                if(seg[k][0] == p[k].getid()){
                    set<int> inPlanar01 = seg[k].getinPlanar01();
                    inPlanar01.insert(pl.getid());
                    seg[k].setinPlanar01(inPlanar01);
                }
                else if(seg[k][1] == p[k].getid()){
                    set<int> inPlanar10 = seg[k].getinPlanar10();
                    inPlanar10.insert(pl.getid());
                    seg[k].setinPlanar10(inPlanar10);
                }
                if(p[k][0] > farpoint[0]){
                    farpoint[0] = p[k][0];
                }
                if(p[k][1] > farpoint[1]){
                    farpoint[1] = p[k][1];
                }
                if(p[k][2] > farpoint[2]){
                    farpoint[2] = p[k][2];
                }
            }
            set<int> inSegment0 = p[0].getinSegment(),
                inSegment1 = p[1].getinSegment(),
                inSegment2 = p[2].getinSegment();
            inSegment0.insert(seg[0].getid());
            inSegment0.insert(seg[2].getid());
            inSegment1.insert(seg[1].getid());
            inSegment1.insert(seg[0].getid());
            inSegment2.insert(seg[2].getid());
            inSegment2.insert(seg[1].getid());
            p[0].setinSegment(inSegment0);
            p[1].setinSegment(inSegment1);
            p[2].setinSegment(inSegment2);
            pl.setexistsegments(existseg);
        }
    }
    for(int k = 0; k < 3; k++){
        farpoint[k] = farpoint[k] + 1;
        points[0] = farpoint;
    }
}


void Data::clear(){
    farpoint = Point(0, 0, 0, 0);
    for(auto i = existpoints.begin(); i != existpoints.end(); i++){
        points[*i].setinYinset(-2);
        points[*i].setinSegment(set<int>());
    }
    existpoints.clear();
    for(auto i = existsegments.begin(); i != existsegments.end(); i++){
        segments[*i].setinYinset(-2);
        segments[*i].setinPlanar(set<int>());
        segments[*i].setinPlanar01(set<int>());
        segments[*i].setinPlanar10(set<int>());
    }
    existsegments.clear();
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        planars[*i].setinYinset(-2);
        planars[*i].setinFace(-2);
        planars[*i].setexistpoints(set<int>());
        planars[*i].setexistsegments(set<int>());
    }
    existplanars.clear();
    for(auto i = existfaces.begin(); i != existfaces.end(); i++){
        faces[*i].setinYinset(-2);
        faces[*i].settype(-2);
    }
    existfaces.clear();
    pastpoints.clear();
}



void Data::intersection(){
    TriangleIntersection functor;
    for(auto i = existplanars.begin(); i != --existplanars.end(); i++){
        for(auto j = ++i; j != existplanars.end(); j++){
            Planar pli = planars[*i],
                plj = planars[*j];
            functor(pli, plj);
        }
    }
    SegmentIntersection functor1;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        functor1(planars[*i]);
    }
}

void Data::triangulation(){
    vector<Planar> triangles;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Triangulation functor;
        Planar pl = Data::planars[*i];
        vector<Planar> parttriangles = functor(pl);
        copy(parttriangles.begin(), parttriangles.end(), triangles.end());
    }
    existplanars.clear();
    for(auto i = triangles.begin(); i != triangles.end(); i++){
        existplanars.insert((*i).getid());
    }
}

void Data::selecttriangles(const Yinset& y1, const Yinset& y2){
    vector<int> delpl;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Planar pl = Data::planars[*i];
        YinsetContainTriangle functor;
        if(pl.getinYinset() == y1.getid()){
            if(functor(y2, pl, 0) == false){
                delpl.push_back(pl.getid());
            }
        }
        else{
            if(functor(y1, pl, 1) == false){
                delpl.push_back(pl.getid());
            }
        }
    }
    for(auto i = delpl.begin(); i != delpl.end(); i++){
        existplanars.erase(*i);
    }
}

void Data::past(){
    existfaces.clear();
    FindNearTriangle functor;
    vector<int> face;
    set<int> remain = existplanars;
    stack<int> s;
    while(!remain.empty()){
        if(s.empty()){
            if(face.size() != 0){
                Face f(face, facesnum++);
                existfaces.insert(f.getid());
                face.clear();
            }
            s.push(*remain.begin());
            remain.erase(remain.begin());
        }
        int k = s.top();
        s.pop();
        face.push_back(k);
        Planar pl = planars[k];
        vector<int> neartriangle = functor(pl);
        if(remain.find(neartriangle[0]) != remain.end()){
            remain.erase(neartriangle[0]);
            s.push(neartriangle[0]);
        }
        if(remain.find(neartriangle[1]) != remain.end()){
            remain.erase(neartriangle[1]);
            s.push(neartriangle[1]);
        }
        if(remain.find(neartriangle[2]) != remain.end()){
            remain.erase(neartriangle[2]);
            s.push(neartriangle[2]);
        }
        if(remain.empty()){
            while(!s.empty()){
                int temp = s.top();
                s.pop();
                face.push_back(temp);
            }
            if(face.size() != 0){
                Face f(face, facesnum++);
                existfaces.insert(f.getid());
                face.clear();
            }
        }
    }
}


void Data::print(ostream& os, const Yinset& y){
    clear();
    load(y);
    map<int, int> printv;
    map<int, int> printvn;
    int kv = 1;
    for(auto i = existpoints.begin(); i != existpoints.end(); i++){
        os << "v " << points[*i] << endl;
        printv.insert(make_pair(*i, kv++));
    }
    //os << endl;
    int kvn = 1;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Planar pl = planars[*i];
        os << "vn " << pl.getnormaldirect() << endl;
        printvn.insert(make_pair(*i, kvn++));
    }
    //os << endl;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Planar pl = planars[*i];
        vector<int> vp = pl.getpoints();
        os << "f "
           << printv[vp[0]] << "/" << 1 << "/" << printvn[*i] << " "
           << printv[vp[1]] << "/" << 1 << "/" << printvn[*i] << " "
           << printv[vp[2]] << "/" << 1 << "/" << printvn[*i] << endl;
    }
    clear();
}

int Data::import(istream& is){
    clear();
    int startpointsid = Data::pointsnum;
    map<int, int> printv;
    map<int, Direction> printvn;
    map<pair<int, int>, int> printseg;
    int kv = 1;
    int kvn = 1;
    string ism,
        sv("v"),
        svn("vn"),
        sf("f"),
        sm("#");
    int s;
    while(is >> ism){
        if(ism == sm){
            is.ignore(256, '\n');
        }
        if(ism == sv){
            Point p;
            is >> p;
            p.setid(pointsnum++);
            existpoints.insert(p.getid());
            if(p > farpoint){
                farpoint[0] = p[0];
                farpoint[1] = p[1];
                farpoint[2] = p[2];
            }
            printv[kv++] = p.getid();
            existpoints.insert(p.getid());
        }
        else if(ism == svn){
            Direction d;
            is >> d;
            printvn.insert(make_pair(kvn++, d));
        }
        else if(ism == sf){
            vector<int> vp;
            vp.resize(3);
            int i;
            Direction normal;
            for(int j = 0; j < 3; j++){
                is >> s;
                //vp[j] = printv[s[0] - static_cast<int>('0')];
                vp[j] = s + startpointsid - 1;
                char x;
                is >> x;
                is >> s;
                is >> x;
                is >> s;
                normal = normal + //printvn[s[4] -  static_cast<int>('0')];
                    printvn[s];
            }
            Direction d1 = points[vp[1]] - points[vp[0]],
                d2 = points[vp[2]] - points[vp[1]];
            if(d1.cross(d2).dot(normal) < 0){
                int temp = vp[0];
                vp[0] = vp[1];
                vp[1] = temp;
            }
            Segment seg0(vp[0], vp[1]),
                seg1(vp[1], vp[2]),
                seg2(vp[2], vp[0]);
            //set<int> s;
            auto it = printseg.find(make_pair(seg0[0], seg0[1]));
            if(it != printseg.end()){
                int id = it->second;
                seg0 = segments[id];
            }
            else{
                seg0.setid(segmentsnum++);
                printseg[make_pair(seg0[0], seg0[1])] = seg0.getid();
                //existsegments.insert(seg0.getid());
            }
            it = printseg.find(make_pair(seg1[0], seg1[1]));
            if(it != printseg.end()){
                int id = it->second;
                seg1 = segments[id];
            }
            else{
                seg1.setid(segmentsnum++);
                printseg[make_pair(seg1[0], seg1[1])] = seg1.getid();
                //existsegments.insert(seg1.getid());
            }
            it = printseg.find(make_pair(seg2[0], seg2[1]));
            if(it != printseg.end()){
                int id = it->second;
                seg2 = segments[id];
            }
            else{
                seg2.setid(segmentsnum++);
                printseg[make_pair(seg2[0], seg2[1])] = seg2.getid();
                //existsegments.insert(seg2.getid());
            }
            if(seg0[0] == vp[0]){
                set<int> inPlanar = seg0.getinPlanar(),
                    inPlanar01 = seg0.getinPlanar01();
                inPlanar.insert(planarsnum);
                inPlanar01.insert(planarsnum);
                seg0.setinPlanar(inPlanar);
                seg0.setinPlanar01(inPlanar01);
            }
            else{
                set<int> inPlanar = seg0.getinPlanar(),
                    inPlanar10 = seg0.getinPlanar10();
                inPlanar.insert(planarsnum);
                inPlanar10.insert(planarsnum);
                seg0.setinPlanar(inPlanar);
                seg0.setinPlanar10(inPlanar10);
            }
            if(seg1[0] == vp[1]){
                set<int> inPlanar = seg1.getinPlanar(),
                    inPlanar01 = seg1.getinPlanar01();
                inPlanar.insert(planarsnum);
                inPlanar01.insert(planarsnum);
                seg1.setinPlanar(inPlanar);
                seg1.setinPlanar01(inPlanar01);
            }
            else{
                set<int> inPlanar = seg1.getinPlanar(),
                    inPlanar10 = seg1.getinPlanar10();
                inPlanar.insert(planarsnum);
                inPlanar10.insert(planarsnum);
                seg1.setinPlanar(inPlanar);
                seg1.setinPlanar10(inPlanar10);
            }
            if(seg2[0] == vp[2]){
                set<int> inPlanar = seg2.getinPlanar(),
                    inPlanar01 = seg2.getinPlanar01();
                inPlanar.insert(planarsnum);
                inPlanar01.insert(planarsnum);
                seg2.setinPlanar(inPlanar);
                seg2.setinPlanar01(inPlanar01);
            }
            else{
                set<int> inPlanar = seg2.getinPlanar(),
                    inPlanar10 = seg2.getinPlanar10();
                inPlanar.insert(planarsnum);
                inPlanar10.insert(planarsnum);
                seg2.setinPlanar(inPlanar);
                seg2.setinPlanar10(inPlanar10);
            }
            vector<int> vseg;
            vseg.push_back(seg0.getid());
            vseg.push_back(seg1.getid());
            vseg.push_back(seg2.getid());
            existsegments.insert(seg0.getid());
            existsegments.insert(seg1.getid());
            existsegments.insert(seg2.getid());
            Planar pl(vp, vseg, planarsnum++, -1, yinsetsnum);
            existplanars.insert(pl.getid());
        }
    }
    farpoint += Direction(1, 1, 1);
    past();
    vector<int> faces(existfaces.size());
    copy(Data::existfaces.begin(), Data::existfaces.end(), faces.begin());
    Yinset anwser(faces, Data::yinsetsnum++);
    anwser.generatorhassmap();
    clear();
    return anwser.getid();
}