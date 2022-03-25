#include "../lib/SplineBuilder.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cassert>

using namespace std;

void _F(const vector<Real> &X, const vector<Real> &Y, const vector<Real> &D, ostream &os) {
    assert(X.size() == Y.size());
    int N = X.size();
    SplineCondition<Vec<1, Real>> cond;
    cond.setN(N);
    for (int i = 0; i < N; ++i) {
        cond.setT(i + 1, X[i]);
        cond.setC(i + 1, 0, Vec<1, Real>{Y[i]});
    }
    cond.setC(1, 1, Vec<1, Real>{D[0]});
    cond.setC(N, 1, Vec<1, Real>{D[1]});

    auto spl = SplineBuilder::Interpolate<1, 3, SplineType::ppForm, BCType::complete>::create(cond);

    int T = 1000;
    for (int i = 0; i <= T; ++i) {
        Real x = X.front() + (Real)i / T * (X.back() - X.front());
        Real y = spl.eval(x)[0];
        os << x << ' ' << y << endl;
    }
}

void F() {
    cout << "--- F ---" << endl;
    cout << "see the programming report" << endl;
    ofstream os("./outs/F.out");
    os << fixed << setprecision(8);
    const int T = 3;
    vector<Real> Xs[T] = {
        {1, 2, 5, 6, 7, 8, 10, 13, 17},
        {17, 20, 23, 24, 25, 27, 27.7},
        {27.7, 28, 29, 30}
    };
    vector<Real> Ys[T] = {
        {3.0, 3.7, 3.9, 4.2, 5.7, 6.6, 7.1, 6.7, 4.5},
        {4.5, 7.0, 6.1, 5.6, 5.8, 5.2, 4.1},
        {4.1, 4.3, 4.1, 3.0}
    };
    vector<Real> Ds[T] = {
        {1.0, -0.67},
        {3.0, -4.0},
        {0.33, -1.5}
    };
    for (int i = 0; i < T; ++i) {
        _F(Xs[i], Ys[i], Ds[i], os);
    }
    os << "---" << endl;
    for (int i = 0; i < T; ++i) {
        if (i == 0) {
            os << Xs[i].front() << ' ' << Ys[i].front() << endl;
        }
        os << Xs[i].back() << ' ' << Ys[i].back() << endl;
    }
}