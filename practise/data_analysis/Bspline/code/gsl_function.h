#ifndef GSL_Function
#define GSL_Function

#include<gsl/gsl_sf_bessel.h>
#include<gsl/gsl_deriv.h>
//#include<gsl/gsl_roots.h>
#include<stdio.h>
#include<iostream>
#include<cassert>
#include<vector>
#include<algorithm>
#include<iterator>

//using namespace std;


class my_f_params{
/**
 * Contain vary numbers for function as coefficient
 *
 * Using vector<double> initiallize and return.
 * get() return these numbers,
 * midpoint is vaule x0 in (x - x0)^k. default is 0.
 */
    std::vector<std::vector<double>> a;
    double midpoint;
public:
    explicit my_f_params(const std::vector<std::vector<double>>& init) : a(init) ,midpoint(0){}
    std::vector<std::vector<double>>& get(){
        return a;
    }
    double& getmid(){
        return midpoint;
    }
    friend std::ostream& operator<<(std::ostream& os, const my_f_params& params ){
        os << params.midpoint << std::endl;
        std::vector<std::vector<double>> a = params.a;
        for(auto i = a.begin(); i != a.end(); i++){
            std::vector<double> b = *i;
            for(auto k = b.begin(); k != b.end(); k++){
                os << *k << " ";
            }
            // std::copy(b.begin(), b.end(),
            //         std::ostream_iterator<double>(os, " "));
            os << std::endl;
        }
        return os;
    }
};

enum ftype{Polynomial = 0, Trigonometric = 1, Fractional = 2};
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
    std::vector<double> a = params->get()[0];
    x = x - params->getmid();
    for_each(a.begin(), a.end(), [&d, x] (double k) {d = d * x + k;} );
    return d;
}

template<class T>
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
double my_f</*Trigonometric*/Fractional>(double x, void* p){
    /**
     * calculate tanx - x
     *
     * x: position where f calculate
     * p: meanless in this function, but to meet requirement of gsl_function
     * return f value
     */
    /*
      assert(p == 0 &&
      "Trigonometric function shouldn't have params");
      double d = 0;
      d = tan(x) - x;
      return d;
    */
    assert(p != 0 &&
           "This is fractional function, should have params");
    my_f_params * params = static_cast<my_f_params*>(p);
    double d1 = 0, d2 = 0;
    std::vector<double> a = params->get()[0],b;
    x = x - params->getmid();
    if(params->get().size() > 1)
        b = params->get()[1];
    for_each(a.begin(), a.end(), [&d1, x] (double k) {d1 = d1 * x + k;});
    assert(d1 != 0 &&
           "Denominator shouldn't be 0.");
    d1 = 1/d1;
    if(b.empty())
        return d1;
    for_each(b.begin(), b.end(), [&d2, x] (double k) {d2 = d2 * x + k;});
    d1 = d2 * d1;
    return d1;
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
    //assert(p == 0 && "Trigonometric function shouldn't have params");
    my_f_params * params = static_cast<my_f_params *>(p);
    x = x - params->getmid();
    double d = 0;
    d = tan(x) - x;
    return d;
}


#endif