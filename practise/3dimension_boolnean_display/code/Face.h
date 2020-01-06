#ifndef FACE_BOOLEAN
#define FACE_BOOLEAN

#include"Data.h"
#include<vector>
#include<utility>

class Face {
    std::vector<int> planars;
    int id;
    int inYinset;
    int type;
public:
    Face(){}
    explicit Face(std::vector<int> vpl, int identity = -1, int inY = -1, int t = -1) : planars(vpl), id(identity), inYinset(inY), type(t) {}
    Face(const Face& f) : planars(f.planars), id(f.id), inYinset(f.inYinset), type(f.type) {}
    Face& operator=(const Face& f){
        Face temp(f);
        std::swap(*this, temp);
        return *this;
    }
    std::vector<int> getplanars() const {
        return planars;
    }
    void setplanars(const vector<int>& vp) {
        planars = vp;
    }
    int getid()const {
        return id;
    }
    void setid(const int i) {
        id = i;
    }
    int getinYinset()const {
        return inYinset;
    }
    void setinYinset(const int i) {
        inYinset = i
    }
    int gettype() const {
        return type;
    }
    void settype(const int i) {
        type = i;
    }
    //bool ifincludeFace(const Face& f) const;
};


#endif