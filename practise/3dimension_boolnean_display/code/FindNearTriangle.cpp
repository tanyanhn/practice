#include"FindNearTriangle.h"
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



vector<int> FindNearTriangle::operator()(const Planar& triangle){
    Segment seg0 = Data::segments[triangle.getsegments()[0]],
        seg1 = Data::segments[triangle.getsegments()[1]],
        seg2 = Data::segments[triangle.getsegments()[2]];
    vector<Segment> vSeg;
    vector<int> anwser;
    vSeg.push_back(seg0); vSeg.push_back(seg1); vSeg.push_back(seg2);
    for(auto i = vSeg.begin(); i != vSeg.end(); i++){
        double angle = 2 * M_PI + 1;
        Segment seg = *i;
        set<int> inPlanar01 = seg.getinPlanar01(),
            inPlanar10 = seg.getinPlanar10();
        if(find(inPlanar01.begin(), inPlanar01.end(), triangle.getid())
           != inPlanar01.end()){
            Direction d = Data::points[(*i)[1]] - Data::points[(*i)[0]];
            int k = -1;
            for(auto j = inPlanar10.begin(); j != inPlanar10.end(); j++){
                double a = triangle.angleBetweenFlats(Data::planars[*j], d);
                if(a < angle){
                    angle = a;
                    k = *j;
                }
            }
            if(k == -1){
                cout << "FindNearTriangle wrong   k = -1: " << triangle.getid();
                char* a = 0;
                cout << *a;
            }
            //set<int> inPlanar10 = seg.getinPlanar10();
            //inPlanar10.erase(k);
            //seg.setinPlanar10(inPlanar10);
            anwser.push_back(k);
        }
        else if(find(inPlanar10.begin(), inPlanar10.end(), triangle.getid())
                != inPlanar10.end()){
            Direction d = Data::points[(*i)[0]] - Data::points[(*i)[1]];
            int k = -1;
            for(auto j = inPlanar01.begin(); j != inPlanar01.end(); j++){
                double a = triangle.angleBetweenFlats(Data::planars[*j], d);
                if(a < angle){
                    angle = a;
                    k = *j;
                }
            }
            if(k == -1){
                cout << "FindNearTriangle wrong : " << triangle.getid();
                char* a = 0;
                cout << *a;
            }
            //set<int> inPlanar01 = seg.getinPlanar01();
            //inPlanar01.erase(k);
            //seg.setinPlanar01(inPlanar01);
            anwser.push_back(k);
        }
        else {
            cout << "FindNearTriangle wrong   else: " << triangle.getid();
            char* a = 0;
            cout << *a;
        }
    }
    return anwser;
}
