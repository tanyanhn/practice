#include"FaceContainFace.h"
#include<vector>
#include"Planar.h"
#include"YinsetContainTriangle.h"

using namespace std;


bool FaceContainFace::operator()(const Face& f1, const Face& f2){
    vector<int> f2Pls = f2.getplanars();
    Planar f2Pl = Data::planars[f2Pls[0]];
    YinsetContainTriangle functor;
    vector<int> v;
    v.push_back(f1.getid());
    Yinset yinf1(v, -1, f1.gettype());
    return functor(yinf1, f2Pl, 1);
}
