#ifndef _PROJECT3_CARDINALBSPLINE_H_
#define _PROJECT3_CARDINALBSPLINE_H_

#include "Config.H"

template <int Order>
constexpr Real CardBSpline(int i, Real t);

template <>
constexpr Real CardBSpline<0>(int i, Real t)
{
    return (t <= i && t > i - 1) ? 1.0 : 0.0;
};

template <>
constexpr Real CardBSpline<1>(int i, Real t)
{
    if (t <= i - 1)
        return 0.0;
    else if (t <= i)
        return t - i + 1.0;
    else
        return CardBSpline<1>(i, 2 * i + 1 - 1 - t);
};

template <>
constexpr Real CardBSpline<2>(int i, Real t)
{
    if (t <= i - 1)
        return 0.0;
    else if (t <= i)
        return (t - i + 1.0) * (t - i + 1.0) / 2.0;
    else if (t <= i + 1)
        return 0.75 - (t - (i + 0.5)) * (t - (i + 0.5));
    else
        return CardBSpline<2>(i, 2 * i + 2 - 1 - t);
};

template <>
constexpr Real CardBSpline<3>(int i, Real t)
{
    if (t <= i - 1)
        return 0.0;
    else if (t <= i)
        return (t - i + 1.0) * (t - i + 1.0) * (t - i + 1.0) / 6.0;
    else if (t <= i + 1)
        return 2.0 / 3.0 - 0.5 * (t - i - 1.0) * (t - i - 1.0) * (t - i + 1.0);
    else
        return CardBSpline<3>(i, 2 * i + 3 - 1 - t);
};

///=================================================

template <int Order>
Real OrdinaryBSpline(const RealVect rv, const Real t);

template <>
Real OrdinaryBSpline<1>(const RealVect rv, const Real t)
{
    if (t <= rv[0])
        return 0.0;
    else if (t <= rv[1])
        return (t - rv[0]) / (rv[1] - rv[0]);
    else if (t <= rv[2])
        return (rv[2] - t) / (rv[2] - rv[1]);
    else
        return 0.0;
};

template <>
Real OrdinaryBSpline<2>(const RealVect rv, const Real t)
{
    if (t <= rv[0])
        return 0.0;
    else if (t <= rv[1])
        return (t - rv[0]) * (t - rv[0]) / (rv[1] - rv[0]) / (rv[2] - rv[0]);
    else if (t <= rv[2])
        return (rv[2] - t) * (t - rv[0]) / (rv[2] - rv[1]) / (rv[2] - rv[0]) + (rv[3] - t) * (t - rv[1]) / (rv[3] - rv[1]) / (rv[2] - rv[1]);
    else if (t <= rv[3])
        return (t - rv[3]) * (t - rv[3]) / (rv[3] - rv[1]) / (rv[3] - rv[2]);
    else
        return 0.0;
};
#else
//do nothing
#endif
