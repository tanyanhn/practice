#ifndef TOLERANCE_BOOLEAN
#define TOLERANCE_BOOLEAN
#include"Flat.h"

class Tol{
public:
    static double t;
    static Flat f;
    static void settol(double tt){
        t = tt;
    }
    static void setsweepflat(Flat ff){
        f = ff;
    }
};

double Tol::t = 1e-5;
Flat Tol::f;

#endif