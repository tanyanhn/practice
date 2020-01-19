#ifndef TOLERANCE_BOOLEAN
#define TOLERANCE_BOOLEAN
//#include"Flat.h"
#include<memory>
class Line;
class Direction;

class Tol{
public:
    static double t;
    static std::unique_ptr<Line> l;
    static std::unique_ptr<Direction> outside;
    static void settol(double tt){
        t = tt;
    }
    // static void setsweepflat(Flat ff){
    //    f = new Flat(ff);
    //}
};

class DoubleComparer : public std::binary_function<double,double,bool>
{
public:
	DoubleComparer( double arg_ = Tol::t ) : epsilon(arg_) {}
	bool operator()( const double &left, const double &right  ) const
        {
            return (abs(left - right) > epsilon) && (left < right);
        }
	~DoubleComparer(){}
private:
	double epsilon;
};

/*
double Tol::t = 1e-5;
std::unique_ptr<Flat*> Tol::f(new Flat);

bool operator<(const double d1, const double d2){
    return d1 < (d2 - Tol::t);
}
*/

#endif