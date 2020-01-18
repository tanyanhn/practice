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
    Segment seg0 = Data::segments[triangle.getsegments().[0]],
        seg1 = Data::segments[triangle.getsegments().[1]],
        seg2 = Data::segments[triangle.getsegments().[2]];
    vector<Segment> vSeg;
    vector<int> anwser;
    vSeg.push_back(seg0); vSeg.push_back(seg1); vSeg.push_back(seg2);
    for(auto i = vSeg.begin(); i != vSeg.end(); i++){
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
            for(auto j = *i.getinPlanar01().begin(); j != *i.getinPlanar01().end(); j++){
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
