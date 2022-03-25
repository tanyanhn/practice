#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <vector>

using Real = double;
using RealVect = std::vector<Real>;
using RealBox = std::vector<RealVect>; 

template <class T>
constexpr T Max(const T &a, const T &b)
{
    return a > b ? a : b;
};

constexpr int fac(const int x)
{
    int f = 1;
    if (x == 0 || x == 1)
        return f;
    else
        return fac(x - 1) * x;
};

#else
//do nothing
#endif
