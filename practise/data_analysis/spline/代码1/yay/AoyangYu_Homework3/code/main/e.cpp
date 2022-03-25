#include "../lib/SplineBuilder.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <cmath>

using namespace std;

pair<Real, Real> gety(Real x) {
    Real u = sqrt(fabs(x)), v = sqrt(3 - x * x);
    Real y1 = (Real)2 / 3 * (u - v);
    Real y2 = (Real)2 / 3 * (u + v);
    return {y1, y2};
}

void _E(int _N, ostream &os) {
    int N = _N / 2, upM = N / 2, downM = (N + 1) / 2;
    Real R = sqrt(3);
    vector<Vec<2, Real>> pts(N + 2);
    for (int i = 0; i <= downM; ++i) {
        Real x = (Real)i / downM * R;
        pts[i + 1] = Vec<2, Real>{x, gety(x).first};
    }
    for (int i = 0; i < upM; ++i) {
        Real x = (Real)i / upM * R;
        pts[N + 1 - i] = Vec<2, Real>{x, gety(x).second};
    }
    vector<Real> t(N + 2);
    t[1] = 0;
    for (int i = 2; i <= N + 1; ++i) {
        t[i] = t[i - 1] + norm(pts[i] - pts[i - 1], 2);
    }
    Real len = t[N + 1];

    Real yd_low = (pts[2][1] - pts[1][1]) / (t[2] - t[1]);
    Real yd_up  = (pts[N + 1][1] - pts[N][1]) / (t[N + 1] - t[N]);

    SplineCondition<Vec<2, Real>> cond;
    cond.setN(N + 1);
    for (int i = 1; i <= N + 1; ++i) {
        cond.setT(i, t[i]);
        cond.setC(i, 0, pts[i]);
    }
    cond.setC(1, 1, Vec<2, Real>{0, yd_low});
    cond.setC(N + 1, 1, Vec<2, Real>{0, yd_up});

    auto spl = SplineBuilder::Interpolate<2, 3, SplineType::ppForm, BCType::complete>::create(cond);

    os << fixed << setprecision(8);
    for (int i = 1; i <= N + 1; ++i) {
        os << pts[i][0] << ' ' << pts[i][1] << endl;
    }
    for (int i = N; i > 1; --i) {
        os << -pts[i][0] << ' ' << pts[i][1] << endl;
    }

    os << "---" << endl;

    int T = 1000;
    vector<Vec<2, Real>> res(T + 1);
    for (int i = 0; i <= T; ++i) {
        Real tt = (Real)i / T * len;
        Vec<2, Real> s = spl.eval(tt);
        os << s[0] << ' ' << s[1] << endl;
        res[i] = s;
    }
    for (int i = T - 1; i > 0; --i) {
        const Vec<2, Real> &s = res[i];
        os << -s[0] << ' ' << s[1] << endl;
    }
}


void E() {
    cout << "--- E ---" << endl;
    cout << "see the programming report" << endl;
    const int T = 3;
    const int Ns[T] = {10, 40, 160};
    const char *names[T] = {"./outs/E_10.out", "./outs/E_40.out", "./outs/E_160.out"};
    for (int i = 0; i < T; ++i) {
        ofstream os(names[i]);
        _E(Ns[i], os);
    }
}