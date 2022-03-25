#include <fstream>
#include <iomanip>
#include <algorithm>
#include "../lib/SplineBuilder.hpp"

using namespace std;

template<int Order, SplineType st>
void prt(ofstream &os, const Spline<1, Order, st> &spl) {
    const int T = 1000;
    const Real L = -5, R = 5;
    os << fixed << setprecision(10) << endl;
    os << "---" << endl;
    for (int i = 0; i <= T; ++i) {
        double x = L + (Real)i / T * (R - L);
        Real y = spl.eval(x)[0];
        os << x << ' ' << y << endl;
    }
}

template<BCType bc>
void _C(ofstream &os, const string &description) {
    auto func = [](Real x) -> Real { return 1 / (1 + x * x); };
    auto func_d = [](Real x) -> Real { return -(2 * x / ((1 + x * x) * (1 + x * x))); };

    SplineCondition<Vec<1, Real>> cond;

    if (bc == BCType::complete) {
        cond.clear();
        cond.setN(11);
        cond.setT(0, -6);
        for (int i = -5; i <= 5; ++i) {
            Real x = i;
            Real y = func(x);
            cond.setC(i + 6, 0, Vec<1, Real>{y});
        }
        cond.setC(1, 1, Vec<1, Real>{func_d(-5)});
        cond.setC(11, 1, Vec<1, Real>{func_d(5)});

        auto spl = SplineBuilder::Interpolate<1, 3, SplineType::cardinalB, BCType::complete>::create(cond);

        prt(os, spl);
        
    } else if (bc == BCType::middleP) {
        cond.clear();
        cond.setN(11);
        cond.setT(0, -6);
        cond.setC(0, 0, Vec<1, Real>{func(-5)});
        cond.setC(11, 0, Vec<1, Real>{func(5)});
        for (int i = 1; i <= 10; ++i) {
            Real x = i - 5.5;
            Real y = func(x);
            cond.setC(i, 0, Vec<1, Real>{y});
        }

        auto spl = SplineBuilder::Interpolate<1, 2, SplineType::cardinalB, BCType::middleP>::create(cond);

        prt(os, spl);

    }
}

void C() {
    cout << "---- C ----" << endl;
    cout << "see the programming report" << endl;
    ofstream complete("./outs/C_complete.out");
    ofstream middleP("./outs/C_middleP.out");
    _C<BCType::complete>(complete, "complete cardinalB");
    _C<BCType::middleP>(middleP, "middleP cardinalB");
}