#ifndef TOLERANCE_BOOLEAN
#define TOLERANCE_BOOLEAN


class Tol{
public:
    static double t;
    static void settol(double tt){
        t = tt;
    }
};

double Tol::t = 1e-5;

#endif