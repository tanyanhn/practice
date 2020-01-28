#ifndef FACECONTAINFACE_BOOLEAN
#define FACECONTAINFACE_BOOLEAN

#include"Face.h"

class FaceContainFace {
public:
    bool operator()(const Face&, const Face&);
};


#endif