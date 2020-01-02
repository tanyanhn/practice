#ifndef FACE
#define FACE

#include"Point.h"
#include"Line.h"
#include<map>

class face{
    GraphLine* outedge;
    map<int, GraphLine*> intedge;
    int i;
public:
    face(GraphLine* l = NULL){
        i = 0;
        outedge = l;
        map<GraphLine*> intedge;
    }
    void setoutedge(GraphLine* l){
        outedge = l;
    }
    void setintedge(GraphLine* l){
        i++;
        intedge[i] = l;
    }
}

#endif
