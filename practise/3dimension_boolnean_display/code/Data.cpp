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


Point Data::farpoint;
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
int Data::pointsnum = 0;
int Data::segmentsnum = 0;
int Data::planarsnum = 0;
int Data::facesnum = 0;
int Data::yinsetsnum = 0;


void Data::intersection(){
    TriangleIntersection functor;
    for(auto i = existplanars.begin(), i != --existplanars.end(), i++){
        for(auto j = ++i, j != existplanars.end(), j++){
            Planar pli = planars[*i],
                plj = planars[*j];
            functor(pli, plj);
        }
    }
}

void Data::triangulation(){
    vector<Planar> triangles;
    for(auto i = existplanars.begin(), i != existplanars.end(), i++){
        Triangulation functor;
        Planar pl = Data::planars[*i];
        vector<Planar> parttriangles = functor(pl);
        copy(parttriangles.begin(), parttriangles.end(), triangles.end());
    }
    existplanars.clear();
    for(auto i = triangles.begin(), i != triangles.end(), i++){
        existplanars.insert((*i).getid());
    }
}

void Data::selecttriangles(const Yinset& y1, const Yinset& y2){
    vector<int> delpl;
    for(auto i = existplanars.begin(), i != existplanars.end(), i++){
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
    for(auto i = delpl.begin(), i != delpl.end(), i++){
        existplanars.erase(*i);
    }
}

void Data::past(){
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
        int k = s.pop();
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
    }
}


void Data::print(ostream& os, const Yinset& y){
    clear();
    load(y);
    map<int, int> printv;
    map<int, int> printvn;
    int kv = 0;
    for(auto i = existpoints.begin(); i != existpoints.end(); i++){
        os << "v " << points[*i] << endl;
        printv.insert(make_pair(*i, kv++));
    }
    os << endl;
    int kvn = 0;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Planar pl = planars[*i];
        os << "vn " << pl.getnormaldirect() << end;
        printvn.insert(make_pair(*i, kvn++));
    }
    os << end;
    for(auto i = existplanars.begin(); i != existplanars.end(); i++){
        Planar pl = planars[*i];
        vector<int> vp = pl.getpoints();
        os << "f "
           << printv[vp[0]] << "/" << 1 << "/" << printvn[*i] << " "
           << printv[vp[1]] << "/" << 1 << "/" << printvn[*i] << " "
           << printv[vp[2]] << "/" << 1 << "/" << printvn[*i] << endl;
    }
}

int Data::import(istream& is){
    clear();
    map<int, int> printv;
    map<int, Direction> printvn;
    int kvn = 0;
    string ism,
        sv("v"),
        svn("vn"),
        sf("f"),
        s;
    while(is >> ism){
        if(ism == sv){
            Point p;
            p.setid(pointsnum++);
            is >> p;
        }
        else if(ism == svn){
            Direction d;
            is >> d;
            printvn.insert(make_pair(kvn++, d));
        }
        else if(ism == sf){
            vector<int> vp;
            int i;
            Direction normal;
            for(int j = 0; j < 3; j++){
                is >> s;
                vp[j] = s[0];
                if(j == 0)
                    normal = printvn[s[4]];
                s.clear();
            }
            Segment seg0(vp[0], vp[1], segmentsnum++),
                seg1(vp[1], vp[2], segmentsnum++),
                seg2(vp[2], vp[0], segmentsnum++);
            if()
        }
    }
}