#ifndef BSPLINE_H
#define BSPLINE_H

#include"gsl_function.h"
#include<lapacke.h>
#include<algorithm>
#include<vector>
#include<utility>
#include<iostream>

//using namespace std;
//typedef double (*gslfunction)(double, void*);

class Bspline{
    /**
     * Base class of Bspline
     *
     * f is value of function in interpolation
     * t is points of interpolation
     *
     */
protected:
    std::vector<double> f;
    std::vector<double> t;
public:
    Bspline(){};
    Bspline(const std::vector<double>& ff, const std::vector<double>& tt) : f(ff), t(tt){};
    virtual ~Bspline(){};
    virtual std::vector<double> operator()(double* start) const;
    /**
     * this is Bspline main function
     *
     * start used to return Bspline start i(the i of first B_i^n)
     *
     * return B_i^n's coefficent in i's order
     */
    virtual void Equationgenerator(double*, double*, const int) const = 0;
    /**
     * Generating the matrix of equations
     *
     * first is A, second is B
     * third is dimension
     *
     * return is change A,B's value
     */
    virtual void Equationsolver(double*, double*, const int) const;
    /**
     * Solver the equations
     *
     * Defaut using LAPACKE_dgesv (inherit and override to using what you want)
     *
     */
    virtual void generateranwser(std::vector<double>& anwser, double* B, double* start) const = 0;
    /**
     * From equations solution get coefficents' of B_I^n
     *
     * anwsers solved in anwser return(in order of i)
     * smallest value of i returned in start.
     *
     */
};


void Bspline::Equationsolver(double* A, double* B, const int N) const{
    int ipiv[N];
    LAPACKE_dgesv(LAPACK_COL_MAJOR, N, 1, A, N, ipiv, B, N);
}

std::vector<double> Bspline::operator()(double* start) const{
    int N = f.size();
    double B[N], A[(N)*(N)];
    for(auto i = 0; i < (N)*(N); i++){
        A[i] = 0;
    }
    Equationgenerator(A, B, N);
    Equationsolver(A, B, N);
    std::vector<double> anwser;
    generateranwser(anwser, B, start);
    return anwser;
}



class quadraticBspline : public Bspline{
protected:
    double fpa, fpb;
public:
    quadraticBspline(const std::vector<double>& ff, const std::vector<double>& tt,
                     double fpaa, double fpbb) : Bspline(ff, tt), fpa(fpaa), fpb(fpbb){}
    quadraticBspline(const std::vector<double>& domain, const std::vector<double>& b_condition, gsl_function g);
    /**
     * quadraticBspline constructor
     *
     * from domain and boundary condition get right Bspline::f and Bspline::t
     * store boundary conditions in fpa,fpb;
     */
    ~quadraticBspline(){};
    //std::vector<double> operator()() const ;
    void Equationgenerator(double*, double*, const int) const;
    void generateranwser(std::vector<double>&, double*, double*) const;
    //void Equationsolver(double*, double*, const int) const;
};

quadraticBspline::quadraticBspline(const std::vector<double>& domain, const std::vector<double>& b_condition, gsl_function g) : fpa(b_condition[0]), fpb(b_condition[1]){
    std::vector<double> x, f;
    int k = int(domain[1] - domain[0] + 0.5);
    x.resize(k);
    f.resize(k);
    for(auto i = 0; i < k; i++){
        x[i] = domain[0] + 0.5 + i;
        f[i] = GSL_FN_EVAL(&g, x[i]);
    }
    Bspline::f = f;
    Bspline::t = x;
}

void quadraticBspline::Equationgenerator(double* A, double* B, const int N) const{
    for(auto i = 1; i < N-1; i++){
        int k = i * (N) + i;
        A[k] = 6;
        A[k-1] = 1;
        A[k+1] = 1;
    }
    A[0] = 5;
    A[1] = 1;
    A[N*N - 1] = 5;
    A[N*N - 2] = 1;
    for(auto i = 0; i < N; i++){
        B[i] = 8 * Bspline::f[i];
    }
    B[0] = B[0] - 2 * fpa;
    B[N-1] = B[N-1] - 2 * fpb;
}

void quadraticBspline::generateranwser(std::vector<double>& anwser, double* B, double* start)const {
    int N = Bspline::f.size();
    *start = t[0] - 1.5;
    anwser.resize(N+2);
    anwser[0] = 2 * fpa - B[0];
    anwser[N+1] = 2 * fpb - B[N-1];
    for(auto i = 0; i < N; i++){
        anwser[i+1] = B[i];
    }
}


class cubicBspline : public Bspline{
protected:
    double fpa, fpb;
public:
    cubicBspline(const std::vector<double>& ff, const std::vector<double>& tt,
                     double fpaa, double fpbb) : Bspline(ff, tt), fpa(fpaa), fpb(fpbb){}
    cubicBspline(const std::vector<double>& domain, const std::vector<double>& b_condition, gsl_function g);
    ~cubicBspline(){};
    //std::vector<double> operator()() const ;
    void Equationgenerator(double*, double*, const int) const;
    void generateranwser(std::vector<double>&, double*, double*) const;
};

cubicBspline::cubicBspline(const std::vector<double>& domain, const std::vector<double>& b_condition, gsl_function g) : fpa(b_condition[0]), fpb(b_condition[1]){
    std::vector<double> x, f;
    int k = int(domain[1] - domain[0] + 1.5);
    x.resize(k);
    f.resize(k);
    for(auto i = 0; i < k; i++){
        x[i] = domain[0] + i;
        f[i] = GSL_FN_EVAL(&g, x[i]);
    }
    Bspline::f = f;
    Bspline::t = x;
}

void cubicBspline::Equationgenerator(double* A, double* B, const int N) const {
    for(auto i = 1; i < N-1; i++){
        int k = i * (N) + i;
        A[k] = 4;
        A[k-1] = 1;
        A[k+1] = 1;
    }
    A[0] = 4;
    A[1] = 1;
    A[N] = A[N] + 1;
    A[N*N - 1] = 4;
    A[N*N - 2] = 1;
    A[N*N - N - 1] = A[N*N - N -1] + 1;
    for(auto i = 0; i < N; i++){
        B[i] = 6 * Bspline::f[i];
    }
    B[0] = B[0] + 2 * fpa;
    B[N-1] = B[N-1] - 2 * fpb;
}

void cubicBspline::generateranwser(std::vector<double>& anwser, double* B, double* start) const {
    int N = Bspline::f.size();
    *start = t[0] - 2;
    anwser.resize(N+2);
    anwser[0] = B[1] - 2 * fpa;
    anwser[N+1] = B[N-2] + 2 * fpb;
    for(auto i = 0; i < N; i++){
        anwser[i+1] = B[i];
    }
}

#endif