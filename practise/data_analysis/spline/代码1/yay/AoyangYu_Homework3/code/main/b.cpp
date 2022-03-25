#include <fstream>
#include <iomanip>
#include <algorithm>
#include "../lib/SplineBuilder.hpp"

using namespace std;

template<int Order, SplineType st>
void prt(ofstream &os, int N, const Spline<1, Order, st> &spl) {
    const int T = 1000;
    const Real L = -1, R = 1;
    os << fixed << setprecision(10) << endl;
    os << "---" << endl;
    os << N << endl;
    for (int i = 0; i <= T; ++i) {
        double x = L + (Real)i / T * (R - L);
        Real y = spl.eval(x)[0];
        os << x << ' ' << y << endl;
    }
}

template<BCType bc>
void _B(ofstream &os, const string &description) {
    const int NN = 5;
    int Ns[NN] = {5, 10, 20, 40, 80};
    Real mxerr[NN];
    auto func = [](Real x) -> Real { return 1 / (1 + 25 * x * x); };
    auto func_d = [](Real x) -> Real { return -(50 * x / ((1 + 25 * x * x) * (1 + 25 * x * x))); };

    SplineCondition<Vec<1, Real>> cond;

    cout << "-- " << description << " --" << endl;
    cout << "max error" << endl;
    cout << scientific << setprecision(5);

    for (int _t = 0; _t < NN; ++_t) {
        int N = Ns[_t];
        cond.clear();
        cond.setN(N + 1);
        for (int i = 0; i <= N; ++i) {
            Real x = -1 + (Real)i / N * 2;
            cond.setT(i + 1, x);
            cond.setC(i + 1, 0, Vec<1, Real>{func(x)});
        }
        cond.setC(1, 1, Vec<1, Real>{func_d(-1)});
        cond.setC(N + 1, 1, Vec<1, Real>{func_d(1)});

        auto spl = SplineBuilder::Interpolate<1, 3, SplineType::ppForm, bc>::create(cond);

        prt(os, N, spl);

        Real &err = mxerr[_t] = 0;
        for (int i = 0; i < N; ++i) {
            Real x = -1 + (Real)(i + i + 1) / N;
            Real y = spl.eval(x)[0];
            Real the = func(x);
            err = max(err, fabs(y - the));
        }
        cout << "N = " << N << ":\t" << err << endl;
    }

    Real lny[NN], lnx[NN];
    transform(begin(mxerr), end(mxerr), lny, [](Real x) -> Real { return log(x); });
    transform(begin(Ns), end(Ns), lnx, [](int N) -> Real { return - log(N / 2.); });
    Real b = ( (lny[3] - lny[0]) / (lnx[3] - lnx[0]) + (lny[4] - lny[1]) / (lnx[4] - lnx[1]) ) / 2;
    cout << "rate of convergence = " << b << endl;
}

void B() {
    cout << "---- B ----" << endl;
    ofstream comp("./outs/B_complete.out");
    ofstream nota("./outs/B_notAknot.out");
    _B<BCType::complete>(comp, "complete cubic spline");
    _B<BCType::notAknot>(nota, "notAknot cubic spline");
}
