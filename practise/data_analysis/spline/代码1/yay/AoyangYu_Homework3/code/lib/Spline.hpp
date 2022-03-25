#ifndef _SPLINE_HPP_
#define _SPLINE_HPP_

#include <vector>
#include <algorithm>
#include <iostream>
#include "config.hpp"
#include "Vec.h"
#include "Polynomial.hpp"
#include "SplineCondition.hpp"
#include "SplineTypes.h"


namespace SplineBuilder {
    template<int _Dim, int _Order, SplineType _st, BCType _bc>
    class Interpolate;
    class SplineHelper;
}

// require Order > 0
template<int Dim, int Order, SplineType st>
class Spline;


template<int Order>
class Spline<0, Order, SplineType::ppForm> {
    template<int _Dim, int _Order, BCType _bc>
    friend class SplineBuilder::Interpolate;
    friend class SplineBuilder::SplineHelper;
private:
    int N;
    std::vector<Real> t;
    std::vector<Polynomial<Order, Real>> piece;
public:
    Spline() : N{0}, t{}, piece{} {}
    const std::vector<Polynomial<Order, Real>>& pieces() const {
        return piece;
    }
    Real eval(Real x) const {
        assert(N == t.size());
        int i;
        if (x < t.front()) i = 1; else
        if (x >= t.back()) i = N - 1; else 
        i = std::upper_bound(t.begin(), t.end(), x) - t.begin();
        return piece[i - 1].eval(x - t[i - 1]);
    }
};


template<int Dim, int Order>
class Spline<Dim, Order, SplineType::ppForm> {
    template<int _Dim, int _Order, BCType _bc>
    friend class SplineBuilder::Interpolate;
    friend class SplineBuilder::SplineHelper;
private:
    int N;
    std::vector<Real> t;
    std::vector<Polynomial<Order, Vec<Dim, Real>>> piece;
public:
    Spline() : N{0}, t{}, piece{} {}
    const std::vector<Polynomial<Order, Vec<Dim, Real>>>& pieces() const {
        return piece;
    }
    Vec<Dim, Real> eval(Real x) const {
        assert(N == t.size());
        int i;
        if (x < t.front()) i = 1; else
        if (x >= t.back()) i = N - 1; else 
        i = std::upper_bound(t.begin(), t.end(), x) - t.begin();
        return piece[i - 1].eval(x - t[i - 1]);
    }
};

/*
template<int Order>
class Spline<1, Order, SplineType::cardinalB> {
    template<int _Dim, int _Order, BCType _bc>
    friend class SplineBuilder::Interpolate;
    friend class SplineBuilder::SplineHelper;
private:
    // it can be implemented that 
    // there is only one Base for each `Order`.
    std::vector<Polynomial<Order, Real>> Base;
    int N;
    int p;
    std::vector<Real> _a;

    void _init_base() {
        using vec = std::vector<Polynomial<Order, Real>>;
        using pol = Polynomial<Order, Real>;
        vec now{pol{1}}, nxt;
        for (int n = 0; n < Order; ++n, nxt.swap(now)) {
            nxt.resize(n + 2);
            nxt[0] = pol{0, (Real)1 / (n + 1)} * now[0];
            for (int k = 1; k <= n; ++k) {
                pol fir = pol{(Real)k, (Real)1} / (n + 1) * now[k];
                pol sec = pol{(Real)(n - k + 2), (Real)(-1)} / (n + 1) * now[k - 1];
                nxt[k] = fir + sec;
            }
            nxt[n + 1] = pol{1, -1} / (n + 1) * now[n];
        }
        Base.swap(now);
    }

public:
    Spline() : Base{}, N{}, p{}, _a{} {
        _init_base();
    }

    // this is only for testing
    void print_base(std::ostream &os) const {
        for (int i = 0; i <= Order; ++i) {
            os << i << ":\t" << Base[i] << std::endl;
        }
    }

    Real eval(Real x) const {
        if (x < p + 1 || x > p + N) return Real{};
        int i = floor(x - p);
        if (i == N) --i;
        Real pos = x - (p + i);
        // now i in [1, N - 1]
        for (int k = 0; k <= Order; ++k) {
            int jp = i + Order - k - 1;
            Real b = Base[k].eval(pos);
            return _a[jp] * b;
        }
    }
};
*/

template<int Dim, int Order>
class Spline<Dim, Order, SplineType::cardinalB> {
    template<int _Dim, int _Order, BCType _bc>
    friend class SplineBuilder::Interpolate;
    friend class SplineBuilder::SplineHelper;
private:
    // it can be implemented that 
    // there is only one Base for each `Order`.
    std::vector<Polynomial<Order, Real>> Base;
    int N;
    int p;
    std::vector<Vec<Dim, Real>> _a;

    void _init_base() {
        using vec = std::vector<Polynomial<Order, Real>>;
        using pol = Polynomial<Order, Real>;
        vec now{pol{1}}, nxt;
        for (int n = 0; n < Order; ++n, nxt.swap(now)) {
            nxt.resize(n + 2);
            nxt[0] = pol{0, (Real)1 / (n + 1)} * now[0];
            for (int k = 1; k <= n; ++k) {
                pol fir = pol{(Real)k, (Real)1} / (n + 1) * now[k];
                pol sec = pol{(Real)(n - k + 2), (Real)(-1)} / (n + 1) * now[k - 1];
                nxt[k] = fir + sec;
            }
            nxt[n + 1] = pol{1, -1} / (n + 1) * now[n];
        }
        Base.swap(now);
    }

public:
    Spline() : Base{}, N{}, p{}, _a{} {
        _init_base();
    }

    Vec<Dim, Real> eval(Real x) const {
        if (x < p + 1 || x > p + N) return Vec<Dim, Real>{};
        int i = floor(x - p);
        if (i == N) --i;
        Real pos = x - (p + i);
        Vec<Dim, Real> ret;
        // now i in [1, N - 1]
        for (int k = 0; k <= Order; ++k) {
            int jp = i + Order - k - 1;
            Real b = Base[k].eval(pos);
            ret += _a[jp] * b;
        }
        return ret;
    }
};

#endif