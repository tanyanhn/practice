#include"Flat.h"
#include"Tol.h"

double Tol::t = 1e-5;
std::unique_ptr<Flat> Tol::f (new Flat);


/*
bool operator<(const double d1, const double d2){
    return d1 < (d2 - Tol::t);
}
*/