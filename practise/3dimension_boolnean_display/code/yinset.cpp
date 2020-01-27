#include"Yinset.h"
#include"STLHead.h"
#include"FunctorHead.h"

using namespace std;

Yinset Yinset::meet(Yinset& y2){
    Data::clear()
    Data::load(*this);
    Data::load(y2);
    Data::intersection();
    Data::triangulation();
    Data::selecttriangles(*this, y2);
    Data::past();
    vector<int> faces;
    copy(Data::existfaces.begin(), Data::existfaces.end(), faces.begin());
    Yinset anwser(faces, Data::yinsetsnum++);
    anwser.generatorhassmap();
    anwser.setpastpoints();
    return anwser;
    Data::clear();
}