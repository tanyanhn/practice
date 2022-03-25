#include <fstream>
#include <iomanip>
#include <algorithm>
#include "../lib/SplineBuilder.hpp"

using namespace std;

template<int Order, SplineType st>
void prt(const Spline<1, Order, st> &spl, const string &desc) {
    auto func = [](Real x) -> Real { return 1 / (1 + x * x); };
    Real ps[] = {-3.5, -3, -0.5, 0, 0.5, 3, 3.5};
    cout << desc << ", absolute errors:" << endl;
    for (Real x: ps) {
        Real y = spl.eval(x)[0];
        Real the = func(x);
        cout << fixed << setprecision(2);
        cout << "x = " << x << ":\t";
        cout << scientific << setprecision(4) << fabs(y - the) << endl;
    }
}

template<BCType bc>
void _D(const string &description) {
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

        prt(spl, description);
        
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

        prt(spl, description);

    }
}

void D() {
    cout << "---- D ----" << endl;
    _D<BCType::complete>("complete cardinalB");
    _D<BCType::middleP>("middleP cardinalB");
}