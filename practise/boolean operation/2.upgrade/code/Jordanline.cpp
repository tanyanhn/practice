#include"Jordanline.h"
#include"Point.h"
#include"Line.h"
using namespace std;



void Jordanline::update(){
    vector<Line>& lines = Sweepline::lines;
    vector<Point>& points = Sweepline::points;
    Point p = points[lines[line[0]][1]];
    int j = 0;
    for(auto i = 1; i < line.size(); i++){
        if(points[lines[line[i]][1]] > p){
            p = points[lines[line[i]][1]];
            j = i;
        }
    }
    if(lines[line[j]].getleftline() == -1) leftjordanline = -1;
    else {
        leftjordanline = lines[lines[line[j]].getleftline()].getinjordanline();
        if(leftjordanline == identity){
            if(j + 1 < line.size()){
                if(lines[line[j + 1]].getleftline() == -1) leftjordanline = -1;
                else leftjordanline = lines[lines[line[j + 1]].getleftline()].getinjordanline();
            }
            else {
                if(lines[line[0]].getleftline() == -1) leftjordanline = -1;
                else leftjordanline = lines[lines[line[0]].getleftline()].getinjordanline();
            }
        }
    }
        Point p1 = points[lines[line[j]][0]],
            p2 = points[lines[line[j]][1]];
        Point p3;
        if(j != line.size() - 1)
            p3 = points[lines[line[j +1]][1]];
        else
            p3 = points[lines[line[0]][1]];
        if((p1 - p2).cross(p2 - p3) < 0) type = 0;
        else {type = 1;}
}



const Spajor Jordanline::generator() {
    vector<int>& existjordanlines = Sweepline::existjordanlines;
    AVLTree<pair<int, int>> mark;
    vector<Jordanline>& jordanlines = Sweepline::jordanlines;
    vector<Spajor>& spajors = Sweepline::spajors;
    vector<int> vvi;
    Jordanline jl(vvi);
    for(auto i = 0; i < existjordanlines.size(); i++){
        jordanlines[existjordanlines[i]].update();
    }
    int k = spajors.size();
    vector<HassNode> vhn(existjordanlines.size() + 1);
    for(int i = 0; i < existjordanlines.size(); i++){
        int j = existjordanlines[i];
        jordanlines[existjordanlines[i]].setinspajor(k);
        mark.add(make_pair(existjordanlines[i], i));
        HassNode hn(j);
        vhn[i] = hn;
    }
    HassNode hn(existjordanlines.size());
    vhn[existjordanlines.size()] = hn;
    for(int i = 0; i < existjordanlines.size(); i++){
        jl = jordanlines[existjordanlines[i]];
        if(jl.getleftjordanline() == -1){
            vhn[i].father = existjordanlines.size();
            vhn[existjordanlines.size()].children.push_back(i);
        }
        else{
            while(jl.gettype() == (jordanlines[existjordanlines[i]].gettype())){
                if(jl.getleftjordanline() == -1) break;
                jl = jordanlines[jl.getleftjordanline()];
            }
            if(jl.gettype() !=  (jordanlines[existjordanlines[i]].gettype())) {
                int j = mark.find(make_pair(jl.getidentity(), 0))->data.second;
                vhn[i].father = j;
                vhn[j].children.push_back(i);
            }
            else if(jl.getleftjordanline() == -1){
                vhn[i].father = existjordanlines.size();
                vhn[existjordanlines.size()].children.push_back(i);
            }
            else if(jl.getleftjordanline() == -2) {
                cout << "Jordanline::generator leftjordanline == -2";
            }
            /*  else {
                int j = mark.find(make_pair(jl.getidentity(), 0))->data.second;
                vhn[i].father = j;
                vhn[j].children.push_back(i);
                }*/
        }
    }
    jl = jordanlines[vhn[vhn[existjordanlines.size()].children[0]].getidentity()];
    bool b;
    if(jl.gettype() == 1) b = false;
    else b = true;
    Spajor spajor(vhn, existjordanlines, b, k);
    spajors.push_back(spajor);
    Sweepline::clean();
    return spajor;
}


void Jordanline::setinspajor(const int j){
    for(auto i = 0; i < line.size(); i++){
        Sweepline::lines[line[i]].setinspajor(j);
    }
}


ostream& operator<<(ostream& os, const Jordanline& jl){
    os << jl.size() << endl;
    int i = 0;
    while(i < jl.size()){
        os << Sweepline::points[Sweepline::lines[jl[i]][0]];
        i++;
    }
    return os;
}