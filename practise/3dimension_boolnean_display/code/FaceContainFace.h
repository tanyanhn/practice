#ifndef FACECONTAINFACE_BOOLEAN
#define FACECONTAINFACE_BOOLEAN

#include"Face.h"

class FaceContainFace {
    bool operator()(const Face&, const Face&);
};


#endif