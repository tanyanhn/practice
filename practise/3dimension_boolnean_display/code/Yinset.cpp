#include"Yinset.h"
#include"STLHead.h"
#include"FunctorHead.h"
#include"HassNode.h"

using namespace std;

Yinset Yinset::meet(const Yinset& y2) const {
    Data::clear();
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
    Data::clear();
    return anwser;
}

Yinset Yinset::complement() const {
    Data::clear();
    Data::load(*this);
    set<int> existpl;
    for(auto i = Data::existplanars.begin(); i != Data::existplanars.end(); i++){
        Planar pl = Data::planars[*i];
        Planar reversepl = pl.overturn();
        existpl.insert(reversepl.getid());
        vector<int> segments = pl.getsegments();
        for(int k = 0; k < 3; k++){
            Segment seg = Data::segments[segments[k]];
            set<int> inPlanar = seg.getinPlanar(),
                inPlanar01 = seg.getinPlanar01(),
                inPlanar10 = seg.getinPlanar10();
            inPlanar.erase(pl.getid());
            inPlanar.insert(reversepl.getid());
            if(inPlanar01.erase(pl.getid()) > 0){
                inPlanar10.insert(reversepl.getid());
            }
            else if(inPlanar10.erase(pl.getid()) > 0){
                inPlanar01.insert(reversepl.getid());
            }
            else{
                cout << "complement wrong : pl.getid() :" << pl.getid() << " " << k;
            }
            seg.setinPlanar(inPlanar);
            seg.setinPlanar01(inPlanar01);
            seg.setinPlanar10(inPlanar10);
        }
    }
    Data::existplanars = existpl;
    Data::past();
    vector<int> faces;
    copy(Data::existfaces.begin(), Data::existfaces.end(), faces.begin());
    Yinset anwser(faces, Data::yinsetsnum++);
    anwser.generatorhassmap();
    anwser.setpastpoints();
    Data::clear();
    return anwser;
}


Yinset Yinset::join(const Yinset& y2) const {
    Yinset revery1 = this->complement(),
        revery2 = y2.complement();
    Yinset reveranwser = revery1.meet(revery2);
    return reveranwser.complement();
}

void Yinset::generatorhassmap(){
    int k = faces.size();
    hassmap.clear();
    hassmap.resize(k);
    int x = 0;
    for(auto i = faces.begin(); i != faces.end(); i++, x++){
        Face f = Data::faces[*i];
        hassmap[x].identity = x;
        hassmap[x].father = -2;
        f.generatortype();
    }
    vector<vector<int>> matrix;
    matrix.resize(k);
    for(int i = 0; i < k; i++){
        matrix[i].resize(k);
    }
    FaceContainFace functor;
    int m = 0;
    for(auto i = faces.begin(); i != faces.end(); i++, m++){
        Face fi = Data::faces[*i];
        int n = 0;
        for(auto j = faces.begin(); j != faces.end(); j++, n++){
            Face fj = Data::faces[*j];
            if(m == n){
                matrix[m][n] = 0;
            }
            else{
                if(functor(fi, fj) == true){
                    matrix[m][n] = 1;
                }
                else {
                    matrix[m][n] = 0;
                }
            }
        }
    }
    vector<int> fathernum(k, 0);
    set<int> root;
    for(auto j = 0; j < k; j++){
        for(auto i = 0; i < k; i++){
            fathernum[j] += matrix[i][j];
        }
    }
    for(auto j = 0; j != k; j++){
        if(fathernum[j] == 0){
            root.insert(j);
            fathernum[j]--;
            hassmap[j].father = -1;
        }
    }
    set<int> temproot = root;
    while(1){
        root = temproot;
        temproot.clear();
        if(root.empty()){
            break;
        }
        for(auto i = root.begin(); i != root.end(); i++){
            int col = *i;
            for(int j = 0; j != k; j++){
                if(matrix[col][j] == 1){
                    fathernum[j]--;
                }
            }
            for(auto j = 0; j != k; j++){
                if(fathernum[j] == 0){
                    temproot.insert(j);
                    fathernum[j]--;
                    hassmap[j].father = col;
                }
            }
        }
    }
    for(auto i = hassmap.begin(); i != hassmap.end(); i++){
        HassNode h = *i;
        if(h.father == -2){
            cout << "generatorhassmap wrong -2";
        }
        if(h.father != -1){
            hassmap[h.father].children.push_back(h.identity);
        }
        else if(h.father = -1){
            static int i = 0;
            if(i == 0){
                type = Data::faces[faces[h.identity]].gettype();
                i = 1;
            }
            if(i == 1 && type != Data::faces[faces[h.identity]].gettype()){
                cout << "Yinset's type has trouble ";
            }
        }
    }
    if(id != -1){
        Data::yinsets[id] = *this;
    }
}