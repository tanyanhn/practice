#ifndef DISCRETESPLINE_H
#define DISCRETESPLINE_H

#include<lapacke.h>
#include<algorithm>
#include<vector>
#include<utility>
#include<iostream>
#include"gsl_function.h"
//#include"Bspline.h"

class DiscreteSpline{
protected:
    std::vector<double> f;
    std::vector<double> t;
public:
    DiscreteSpline(){}
    DiscreteSpline(const std::vector<double>& ff, const std::vector<double>& tt) : f(ff), t(tt){
        assert(ff.size() == tt.size() &&
               "the number of interpolation points is different from values' .");
    };
    virtual ~DiscreteSpline(){};
    virtual std::vector<std::pair<my_f_params,std::vector<double>>> operator()() const = 0;
    virtual void Equationgenerator(double*, double*, const int) const = 0;
    virtual my_f_params Hermiteinterpolation(const std::vector<double>& x, const std::vector<double>& f, const std::vector<std::vector<double>>& fp) const = 0 ;
    virtual void Equationsolver(double*, double*, const int) const;
    virtual std::vector<std::pair<my_f_params,std::vector<double>>> generatoranwser(double* B) const = 0;
};

void DiscreteSpline::Equationsolver(double* A, double* B, const int N) const{
    int ipiv[N];
    LAPACKE_dgesv(LAPACK_COL_MAJOR, N, 1, A, N, ipiv, B, N);
}


class DiscreteCompletecubicSpline : public DiscreteSpline{
    double fpa, fpb;
public:
    DiscreteCompletecubicSpline(const std::vector<double>& ff, const std::vector<double>& tt,
                                double fpaa, double fpbb) : DiscreteSpline(ff, tt),
                                                            fpa(fpaa), fpb(fpbb){}
    void Equationgenerator(double*, double*, const int) const;
    std::vector<std::pair<my_f_params,std::vector<double>>> operator()() const;
    my_f_params Hermiteinterpolation(const std::vector<double>& x, const std::vector<double>& f, const std::vector<std::vector<double>>& fp) const;
    std::vector<std::pair<my_f_params,std::vector<double>>> generatoranwser(double* B) const;
};

std::vector<std::pair<my_f_params,std::vector<double>>> DiscreteCompletecubicSpline::operator()() const{
    int N = f.size();
    double A[(N-2)*(N-2)], B[N-2];
    for(auto i = 0; i < (N-2)*(N-2); i++){
        A[i] = 0;
    }
    Equationgenerator(A, B, N-2);
    Equationsolver(A, B, N-2);
    return generatoranwser(B);
}


void DiscreteCompletecubicSpline::Equationgenerator(double* A, double* B, const int N) const{
    double mu[N], lam[N];
    for(auto i = 0; i < N; i++){
        mu[i] = (t[i+1] - t[i]) / (t[i+2] - t[i]);
        lam[i] = (t[i+2] - t[i+1]) / (t[i+2] - t[i]);
    }
    A[0] = 2;
    A[1] = lam[1];
    A[N*N - 1] = 2;
    A[N*N - 2] = mu[N-2];
    for(auto i = 1; i < N-1; i++){
        int k = i * N + i;
        A[k] = 2;
        A[k-1] = mu[i-1];
        A[k+1] = lam[i+1];
    }
    for(auto i = 0; i < N; i++){
        B[i] = 3 * mu[i] * (f[i+1] - f[i+2]) / (t[i+1] - t[i+2]) +
            3 * lam[i] * (f[i] - f[i+1]) / (t[i] - t[i+1]);
    }
    B[0] = B[0] - lam[0] * fpa;
    B[N-1] = B[N-1] - mu[N-1] * fpb;
}

my_f_params DiscreteCompletecubicSpline::Hermiteinterpolation(const std::vector<double>& x, const std::vector<double>& f, const std::vector<std::vector<double>>& fp) const{
    std::vector<std::vector<double>> a;
    std::vector<double> params;
    double K = (f[0] - f[1]) / (x[0] - x[1]);
    params.push_back((fp[0][0] + fp[0][1] - 2 * K) /
                     ((x[1] - x[0]) * (x[1] - x[0])));
    params.push_back((3 * K - 2 * fp[0][0] - fp[0][1]) /
                     (x[1] - x[0]));
    params.push_back(fp[0][0]);
    params.push_back(f[0]);
    a.push_back(params);
    my_f_params anwser(a);
    anwser.getmid() = x[0];
    return anwser;
}

std::vector<std::pair<my_f_params,std::vector<double>>> DiscreteCompletecubicSpline::generatoranwser(double* B) const{
    int N = f.size();
    std::vector<std::pair<my_f_params,std::vector<double>>> anwser;
    std::vector<double> xbegin({t[0], t[1]}), fvbegin({f[0], f[1]});
    std::vector<std::vector<double>> fpbegin({std::vector<double>({fpa, B[0]})});
    my_f_params parambegin = Hermiteinterpolation(xbegin, fvbegin, fpbegin);
    parambegin.getmid() = t[0];
    anwser.push_back(std::make_pair(parambegin, std::vector<double>({t[0], t[1]})));
    for(auto i = 1; i < N-2; i++){
        std::vector<double> x({t[i], t[i+1]}), fv({f[i], f[i+1]});
        std::vector<std::vector<double>> fp({std::vector<double>({B[i-1], B[i]})});
        my_f_params param = Hermiteinterpolation(x, fv, fp);
        param.getmid() = t[i];
        anwser.push_back(std::make_pair(param, std::vector<double>({t[i], t[i+1]})));
    }
    std::vector<double> xend({t[N-2], t[N-1]}), fvend({f[N-2], f[N-1]});
    std::vector<std::vector<double>> fpend({std::vector<double>({B[N-3], fpb})});
    my_f_params paramend = Hermiteinterpolation(xend, fvend, fpend);
    paramend.getmid() = t[N-2];
    anwser.push_back(std::make_pair(paramend, std::vector<double>({t[N-2], t[N-1]})));
    return anwser;
}


#endif