#include <algorithm>
#include "catch.hpp"
#include "../lib/SplineBuilder.hpp"
m
static const Real eps = 1e-8;

bool fequal(Real x, Real y) {
    return fabs(x - y) < eps;
}

TEST_CASE("Spline Builder", "[spl_builder]") {

    SECTION("ppForm:complete") {

        SplineCondition<Vec<2, Real>> cond;

        int N = 5;
        Real t[5] = {1,2,3,4,6};
        Real f[5];
        std::transform(t , t + N, f, [](Real x)->Real{return log(x);});

        cond.setN(N);
        for (int i = 1; i <= N; ++i) {
            cond.setT(i, t[i - 1]);
            cond.setC(i, 0, Vec<2, Real>{t[i - 1], f[i - 1]});
        }
        cond.setC(1, 1, Vec<2, Real>{1, 1 / t[0]});
        cond.setC(N, 1, Vec<2, Real>{1, 1 / t[N - 1]});
        
        auto spl = SplineBuilder::Interpolate<2, 3, SplineType::ppForm, BCType::complete>::create(cond);

        Real xs[6] = {1.6000000000, 2.8250000000, 4.5000000000, 5.0000000000, 5.3000000000, 5.3000000000};
        Real ss[6] = {0.4745653306, 1.0382037033, 1.5042345783, 1.6097702877, 1.6679832033, 1.6679832033};

        for (int i = 0; i < 6; ++i) {
            auto s = spl.eval(xs[i]);
            REQUIRE(fequal(s[0], xs[i]));
            REQUIRE(fequal(s[1], ss[i]));
        }

    }

    SECTION("ppForm:notAknot") {
        SplineCondition<Vec<2, Real>> cond;

        int N = 5;
        Real t[5] = {1, 3, 7, 9, 12};
        Real f[5] = {2, 5, 1, 3, 3};

        cond.setN(N);
        for (int i = 1; i <= N; ++i) {
            cond.setT(i, t[i - 1]);
            cond.setC(i, 0, Vec<2, Real>{t[i - 1], f[i - 1]});
        }
        
        auto spl = SplineBuilder::Interpolate<2, 3, SplineType::ppForm, BCType::notAknot>::create(cond);

        // piece[0] and piece[1], piece[N - 3] and piece[N - 2] should be 
        // identical, respectively. Check this my evaluate at 4 points.
        auto piece = spl.pieces();
        for (int i = 0; i < 5; ++i) {
            Real fir = piece[0].eval(i - t[0])[1];
            Real sec = piece[1].eval(i - t[1])[1];
            Real one = piece[N - 3].eval(i - t[N - 3])[1];
            Real two = piece[N - 2].eval(i - t[N - 2])[1];
            REQUIRE(fequal(fir, sec));
            REQUIRE(fequal(one, two));
        }
    }

    SECTION("ppForm:periodic") {
        SplineCondition<Vec<2, Real>> cond;

        int N = 5;
        Real t[5] = {1, 2, 3, 4, 6};
        Real f[5] = {3, 5, 4, 7};

        cond.setN(N);
        for (int i = 1; i < N; ++i) {
            cond.setT(i, t[i - 1]);
            cond.setC(i, 0, Vec<2, Real>{t[i - 1], f[i - 1]});
        }
        cond.setT(N, t[4]);
        
        auto spl = SplineBuilder::Interpolate<2, 3, SplineType::ppForm, BCType::periodic>::create(cond);

        for (int i = 0; i < 4; ++i) {
            Real app = spl.eval(t[i])[1];
            REQUIRE(fequal(app, f[i]));
        }

        auto fir = spl.pieces().front(), lst = spl.pieces().back();
        Real fir_pos = 0, lst_pos = t[4] - t[3];
        for (int i = 0; i <= 2; ++i, fir = fir.derivative(), lst = lst.derivative()) {
            Vec<2, Real> one = fir.eval(fir_pos);
            Vec<2, Real> two = lst.eval(lst_pos);
            REQUIRE(fequal(one[0], two[0]));
            REQUIRE(fequal(one[1], two[1]));
        }
    }

    SECTION("ppForm:linear") {
        SplineCondition<Vec<2, Real>> cond;

        int N = 5;

        Real xs[5] = {1, 3, 5, 6, 7};
        Real ys[5] = {2, -1, 3, 4, 1};

        cond.setN(5);
        for (int i = 1; i <= N; ++i) {
            cond.setT(i, i);
            cond.setC(i, 0, Vec<2, Real>{xs[i - 1], ys[i - 1]});
        }

        auto spl = SplineBuilder::Interpolate<2, 1, SplineType::ppForm, BCType::linear>::create(cond);

        const int T = 7;
        Real ts[7] = {123, 252, 476, 508, 700, 900, 1000};
        Vec<2, Real> ps[7] = {{1.9840000000, 0.5240000000}, {3.0160000000, -0.9680000000}, {4.8080000000, 2.6160000000}, {5.0320000000, 3.0320000000}, {5.8000000000, 3.8000000000}, {6.6000000000, 2.2000000000}, {7.0000000000, 1.0000000000}};

        for (int i = 0; i < T; ++i) {
            Vec<2, Real> res = spl.eval(1 + ts[i] / 250.);
            REQUIRE(fequal(res[0], ps[i][0]));
            REQUIRE(fequal(res[1], ps[i][1]));
        }
    }

    SECTION("cardinalB:complete") {
        SplineCondition<Vec<2, Real>> cond;

        int N = 5;
        Real t[5] = {1,2,3,4,6};
        Real f[5];
        std::transform(t , t + N, f, [](Real x)->Real{return log(x);});

        cond.setN(N);
        cond.setT(0, 0);
        for (int i = 1; i <= N; ++i) {
            cond.setT(i, i);
            cond.setC(i, 0, Vec<2, Real>{t[i - 1], f[i - 1]});
        }
        cond.setC(1, 1, Vec<2, Real>{1, 1 / t[0]});
        cond.setC(N, 1, Vec<2, Real>{1, 1 / t[N - 1]});
        
        auto pp = SplineBuilder::Interpolate<2, 3, SplineType::ppForm, BCType::complete>::create(cond);
        auto bs = SplineBuilder::Interpolate<2, 3, SplineType::cardinalB, BCType::complete>::create(cond);

        for (int i = 0; i <= 40; ++i) {
            Real x = 1 + i / 40. * 4;
            auto fir = pp.eval(x);
            auto sec = bs.eval(x);
            REQUIRE(fequal(fir[0], sec[0]));
            REQUIRE(fequal(fir[1], sec[1]));
        }
    }

    SECTION("cardinalB:middleP") {
        SplineCondition<Vec<2, Real>> cond;

        int N = 5;
        Real t[6] = {1,1.5,2.5,3.5,4.5,5};
        Real f[6] = {2,3,-4,1,0,6};
        // transform(begin(t), end(t), f, [](Real x)->Real{return log(x);});

        cond.setN(N);
        cond.setT(0, 0);
        for (int i = 0; i <= N; ++i) {
            cond.setC(i, 0, Vec<2, Real>{t[i], f[i]});
        }
        
        auto spl = SplineBuilder::Interpolate<2, 2, SplineType::cardinalB, BCType::middleP>::create(cond);

        for (int i = 0; i <= N; ++i) {
            auto res = spl.eval(t[i]);
            REQUIRE(fequal(res[0], t[i]));
            REQUIRE(fequal(res[1], f[i]));
        }
    }

}
