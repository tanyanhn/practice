#ifndef YINSETCONTAINTRIANGLE_BOOLEAN
#define YINSETCONTAINTRIANGLE_BOOLEAN

#include"Planar.h"
#include"Yinset.h"

class YinsetContainTriangle {
    enum{AddOverlap = 0, notAddOverlap = 1}
    bool operator()(const Yinset& , const Planar&, int);
};


#endif