#ifndef _SPLINE_CONDITION_HPP_
#define _SPLINE_CONDITION_HPP_

#include <vector>
#include "config.hpp"
#include "SplineTypes.h"

namespace SplineBuilder {
    template<int _Dim, int _Order, SplineType _st, BCType _bc>
    class Interpolate; 
}

template<typename ValType>
class SplineCondition {
    template<int _Dim, int _Order, BCType _bc>
    friend class SplineBuilder::Interpolate;
private:
    size_t N;
    std::vector<Real> t;
    std::vector<std::vector<ValType>> c;
public:
    SplineCondition() : N{}, t{}, c{} {}
    void clear() {
        N = 0;
        t.clear();
        c.clear();
    }
    void setN(size_t N) {
        this->N = N;
        t.assign(N + 1, (Real)0);
        c.reserve(N + 1);
    }
    int getN() const {
        return N;
    }
    void setT(size_t i, Real u) {
        t[i] = u;
    }
    Real getT(size_t i) const {
        return t[i];
    }
    void setC(size_t i, size_t j, const ValType &v) {
        if (i >= c.size()) c.resize(i + 1);
        if (j >= c[i].size()) c[i].resize(j + 1);
        c[i][j] = v;
    }
    const ValType& getC(size_t i, size_t j) const {
        static ValType def{};
        if (i >= c.size()) return def;
        if (j >= c[i].size()) return def;
        return c[i][j];
    }
};

#endif