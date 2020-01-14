#ifndef YINSET_BOOLEAN
#define YINSET_BOOLEAN

#include"Data.h"
#include"HassNode.h"
#include<vector>
#include<utility>

class HassNode;

class Yinset{
    std::vector<int> faces;
    std::vector<HassNode> hassmap;
    int id;
    int type;
public:
    explicit Yinset(std::vector<int> vf, int identity = -1, int t = -1) : faces(vf), id(identity), type(t) {}
    Yinset(const Yinset& y) : faces(y.faces), hassmap(y.hassmap), id(y.id), type(y.type) {}
    Yinset& operator=(const Yinset& y){
        Yinset temp(y);
        std::swap(*this, temp);
        return *this;
    }
    std::vector<int> getfaces() const {
        return faces;
    }
    void setfaces(const std::vector<int>& vf){
        faces = vf;
        if(id != -1){
            Data::yinsets[id] = *this;
        }
    }
    std::vector<HassNode> gethassmap() const {
        return hassmap;
    }
    void sethassmap(const std::vector<HassNode>& vh){
        hassmap = vh;
        if(id != -1){
            Data::yinsets[id] = *this;
        }
    }
    int getid() const {
        return id;
    }
    void setid(const int i){
        id = i;
        if(id != -1){
            Data::yinsets[id] = *this;
        }
    }
    int gettype() const {
        return type;
    }
    void settype(const int i){
        type = i;
        if(id != -1){
            Data::yinsets[id] = *this;
        }
    }
    //void generatorhassmap();
};

#endif