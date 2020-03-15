#include<gsl/gsl_sf_bessel.h>
#include<gsl/gsl_deriv.h>
//#include<gsl/gsl_roots.h>
#include<stdio.h>
#include<iostream>
#include<cassert>
#include<vector>
#include<algorithm>

using namespace std;


class my_f_params{
/**
 * Contain vary numbers for function as coefficient
 *
 * Using vector<double> initiallize and return.
 * get() return these numbers,
 */
    vector<double> a;
public:
    explicit my_f_params(const vector<double>& init) : a(init){}
    vector<double>& get(){
        return a;
    }
};

enum ftype{Polynomial = 0, Trigonometric = 1};
/**
 * Defining type of function that we are coming to calculate.
 **/

template<int T>
double my_f(double x, void* p){
    /**
     * template represent function f coming calculate
     *
     * x: position where f calculate
     * p: When my_f is default Polynomial p point to class my_f_params.
     * return f value in point x.
     */
    assert(T == Polynomial &&
           "Default function is polunomial, otherwise you have to specialize your my_f function");
    my_f_params * params = static_cast<my_f_params *>(p);
    double d = 0;
    vector<double> a = params->get();
    for_each(a.begin(), a.end(), [&d, x] (int k) {d = d * x + k;} );
    return d;
}

template<ftype ft, class T>
gsl_function f_factory(T* function, void* params = 0){
    /**
     * factory function create gsl_function for gsl
     *
     * function point to function calculate
     * params: is coefficient when function is Polynomial
     * return gsl_function is used to defferential
     */
    gsl_function F;
    F.function = reinterpret_cast<double (*)(double, void*)>(function);
    F.params = params;
    return F;
}

template<>
double my_f<Trigonometric>(double x, void* p){
    /**
     * calculate tanx - x
     *
     * x: position where f calculate
     * p: meanless in this function, but to meet requirement of gsl_function
     * return f value
     */
    assert(p == 0 &&
           "Trigonometric function shouldn't have params");
    double d = 0;
    d = tan(x) - x;
    return d;
}

double Newtonm(int steps, double it, gsl_function& F, double epsilon = 1e-10, double eta = 1e-10){
    /**
     * print fvalue x position and Newton's method iteration item fvalue/fprime.
     *
     * steps: times of Newton iterations.
     * it: Newton's method start point
     * F: function in gsl be used to calculate value and prime value.
     *
     * Print every step some variable.And return iteration result at last satisfy |F(x)| < epsilon or |fvalue/fprime| < eta or finish steps .
     */
    cout.precision(7);
    //cout.width(7);
    for(int i = 0 ; i < steps; i++){
        double fvalue, fprime, error;
        fvalue = GSL_FN_EVAL(&F, it);
        gsl_deriv_central(&F, -1, 0.1, &fprime, &error);
        cout << "f :" << fvalue << " it :" << it <<
            " f/fp: " << fvalue/fprime << endl;
        if(fabs(fvalue/fprime) < eta || fvalue < epsilon)
            return it;
        it = it - fvalue/fprime;
    }
    return it;
}

int main(int argc, char *argv[])
{
    double coefficient[] = {4.0, -2.0, 0.0, 3.0};
    my_f_params params(vector<double>(coefficient,
                                      coefficient + sizeof(coefficient)/sizeof(double)));
    gsl_function F1 = f_factory<Polynomial>(&my_f<Polynomial>, &params);
    double x = -1;
    int steps = 10;
    //Newtonm(steps, x, F1);
    gsl_function F2 = f_factory<Trigonometric>(&my_f<Trigonometric>, 0);
    double x1= 4.5,
        x2 = 7.7;
    cout << Newtonm(steps, x1, F2) << endl;
    cout << endl;
    cout << Newtonm(steps, x2, F2) << endl;
    return 0;
}
