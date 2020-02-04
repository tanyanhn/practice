#ifndef FACE_BOOLEAN
#define FACE_BOOLEAN

#include"Data.h"
#include<vector>
#include<utility>
#include"STLHead.h"

class Face {
    std::vector<int> planars;
    int id;
    int inYinset;
    int type;
public:
    Face(){}
    explicit Face(std::vector<int> vpl, int identity = -1, int inY = -1, int t = -1) : planars(vpl), id(identity), inYinset(inY), type(t) {
        if(id != -1){
            Data::faces[id] = *this;
        }
    }
    Face(const Face& f)// : planars(f.planars), id(f.id), inYinset(f.inYinset), type(f.type)
        {
            *this = f;
        }
    Face& operator=(const Face& f){
        planars = f.planars;
        id = f.id;
        inYinset = f.inYinset;
        type = f.type;
        return *this;
        /*
        Face temp(f);
        std::swap(*this, temp);
        return *this;
        */
    }
    std::vector<int> getplanars() const {
        return planars;
    }
    void setplanars(const std::vector<int>& vp) {
        planars = vp;
        if(id != -1){
            Data::faces[id] = *this;
        }
    }
    int getid()const {
        return id;
    }
    void setid(const int i) {
        id = i;
        if(id != -1){
            Data::faces[id] = *this;
        }
    }
    int getinYinset()const {
        return inYinset;
    }
    void setinYinset(const int i) {
        inYinset = i;
        if(id != -1){
            Data::faces[id] = *this;
        }
    }
    int gettype() const {
        return type;
    }
    void settype(const int i) {
        type = i;
        if(id != -1){
            Data::faces[id] = *this;
        }
    }
    void generatortype();
    //friend std::ostream& operator<<(ostream& os, const Face& f);
    //bool ifincludeFace(const Face& f) const;
};


#endif