#include"Line.h"
#include"Tol.h"
#include"Direction.h"

double Tol::t = 1e-5;
std::unique_ptr<Direction> Tol::outside(new Direction);
std::unique_ptr<Line> Tol::l (new Line);


/*
bool operator<(const double d1, const double d2){
    return d1 < (d2 - Tol::t);
}
*/