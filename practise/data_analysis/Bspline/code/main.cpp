#include"Bspline.h"
#include<fstream>
#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>
#include<memory>

using namespace std;

template<class T>
unique_ptr<Bspline> Bspline_factory(const vector<double>& domain, const vector<double>& b_condition, gsl_function function = gsl_function()){
    /**
     * Bspline factory
     *
     * domain is domain of interpolants
     * b_condition is boundary conditions
     * gsl_function is function to interpolation
     * (if can't expressed as gsl_function, you will have specificalize this factory to suitable)
     *
     * return a smartpoint that point to a Bspline's derived class.
     */
    return unique_ptr<Bspline>(static_cast<Bspline*>(new T(domain, b_condition, function)));
}


/**
 * template function : calculate cardinal B-spline
 *
 * @param x   calculate B value in point x
 * @param i   i in B-spline B_i^n ,needn't be int but interval is 1
 * @param n   n in B-spline B_i^n , have to define in enum Bsplinetype first.
 *
 * @return    B_i^n(x).
 */
template<int N>
double CardinalBspline(const double x, const double i){
    return ((x - i + 1)/(N)) * CardinalBspline<N-1>(x, i) +
        ((i + N - x)/(N)) * CardinalBspline<N-1>(x, i + 1);
}

template<>
double CardinalBspline<0>(const double x, const double i){
    if(x > i - 1 && x <= i)
        return 1;
    else
        return 0;
}

/**
 * used for CardinalBspline template parameters,
 */
enum Bsplinetype{
    zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5,
};


/**
 * Calculating functions of B_i^n
 *
 * usually represent B-spline function
 *
 *@param coeff     coeffecient of these function
 *@param x         value point
 *@param start     The smallest i in thess B_i^n. and coeff[k] is coeffecient of B_{i+k}^n.
 *
 *@return value in x of these B-spline
 */
template<Bsplinetype n>
double Bsplinefunc(const vector<double>& coeff, double x, double start){
    //int k = coeff.size();
    double d = 0;
    //double a = coeff[0];
    //d= d + a * CardinalBspline<n>(x, start);
     for_each(coeff.begin(), coeff.end(), [&d, &start, x] (double a) {
                                             d = d + a * CardinalBspline<n>(x, start);
                                             start++;
        });
     return d;
}


/**
 * print interpolation error in some points
 *
 * @param coeff       these coeffecient
 * @param x           points where gone to print error in.
 * @param start       the smallest i of B_i^n
 * @param g           function that interpolated, used to computer the error
 *
 * will print x and error in cout .
 */
template<Bsplinetype n>
void printerror(const vector<double>& coeff, const vector<double>& x, double start, gsl_function& g){
    cout << "interpolation Bpsline type : " << n << endl;
    for_each(x.begin(), x.end(), [&coeff, &g, start](double x) {
                                     cout << "interpolate point x : " << x
                                          << "  interpolate value f : " << Bsplinefunc<n>(coeff, x, start) - GSL_FN_EVAL(&g, x) << endl;
                                 });
}


/**
 * By type of Bspline, function and boundary condition to interpolate
 *
 * @param os       output ostream
 * @param domain   function's domain that gone to be interpolated
 * @param b_condition   boundary condition
 * @param function     the function used to be interpolated.
 * @param T        type of B-spline type
 *
 * @return         return interplation coeffecient and start point.
 */
template<class T>
pair<double, vector<double>> interpolation(ostream& os, const vector<double>& domain, const vector<double>& b_condition, gsl_function function = gsl_function()){
    unique_ptr<Bspline> quadBs = Bspline_factory<T>(domain, b_condition,
                                                                   function);
    double start;
    vector<double> anwser = (*quadBs)(&start);
    //printerror<two>(quadanwser, interpolations, start, g);
    os << start << endl;
    copy(anwser.begin(), anwser.end(),
         ostream_iterator<double>(os, " "));
    os << endl;
    return make_pair(start, anwser);
}

int main(int argc, char *argv[])
{
    string s("output/");
    ofstream os1(s + argv[1]);
    ofstream os2(s + argv[2]);
    vector<double> interpolations = {-3.5, -3.0, -0.5, 0, 0.5, 3.0, 3.5};
    vector<double> coe = {1, 0, 1}, domain = {-5, 5};
    vector<double> b_condition1 = {1/26.0, 1.0/26},
        b_condition2 = {10.0 / (26 * 26), -10.0 / (26 * 26)};
    vector<vector<double>> params(1,coe);
    gsl_function g = f_factory(&my_f<Fractional>, &params);
    pair<double, vector<double>> anwser =
        interpolation<quadraticBspline>(os1, domain, b_condition1, g);
    printerror<two>(anwser.second, interpolations, anwser.first, g);
    anwser = interpolation<cubicBspline>(os2, domain, b_condition2, g);
    printerror<three>(anwser.second, interpolations, anwser.first, g);
    return 0;
}
