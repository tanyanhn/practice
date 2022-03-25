
/**
 * @file Polynomial.H
 * @brief 一个描述一元实系数多项式的模板类，可用于加，减，乘，求导，求值，与格式化输出。
 * T 可以是 数， 也可以是 方阵 等具有域与线性空间结构的抽象类。
 * Polynomial的模板参数Order 等于 对应多项式数学意义下的（deg+1）。
 * @author htli (3180102114@zju.edu.cn)
 * @version 2.0
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021  linhuo2020
 * 
 */
#ifndef _PROJECT3_POLYNOMIAL_H_
#define _PROJECT3_POLYNOMIAL_H_

#include <iostream>
#include <vector>
#include <cmath>
#include "Config.H"

template <int Order, class CoefType>
class Polynomial;

template <int Order1, int Order2, class CoefType>
const Polynomial<Max<int>(Order1, Order2), CoefType>
operator+(const Polynomial<Order1, CoefType> &_p1, const Polynomial<Order2, CoefType> &_p2);

template <int Order1, int Order2, class CoefType>
const Polynomial<Max<int>(Order1, Order2), CoefType>
operator-(const Polynomial<Order1, CoefType> &_p1, const Polynomial<Order2, CoefType> &_p2);

template <int Order1, int Order2, class CoefType>
const Polynomial<Order1 + Order2 - 1, CoefType>
operator*(const Polynomial<Order1, CoefType> &_p1, const Polynomial<Order2, CoefType> &_p2);

template <int Ord, class CT>
const Polynomial<Ord, CT>
multiply_overflow(const Polynomial<Ord, CT> &_p1, const Polynomial<Ord, CT> &_p2);

template <int Order, class CoefType>
const Polynomial<Order, CoefType>
operator*(const Polynomial<Order, CoefType> &_p, const Real &_x);

template <int Ord, class CT>
std::ostream &operator<<(std::ostream &os, const Polynomial<Ord, CT> &_p);

template <int Order, class CoefType>
class Polynomial
{
protected:
    ///
    /**
     * from constant term, to highest order term.
     */
    CoefType Coef_[Order];

public:
    ///
    /**
     * Get & Set.
     */
    Polynomial() = default;
    Polynomial(const std::vector<CoefType> &_coefs) { this->setCoefs(_coefs); };
    ~Polynomial() = default;
    void setCoefs(const std::vector<CoefType> &_coefs)
    {
        for (int i = 0; i < Order; i++)
            Coef_[i] = _coefs[i];
    };

  
    const std::vector<CoefType> getCoefs() const { return Coef_; };
    const CoefType &operator[](int i) const { return Coef_[i]; };
    CoefType &operator[](int i) { return Coef_[i]; };
    ///
    /**
     * Elementary Operations
     */
    template <int Order1, int Order2, class CT>
    friend const Polynomial<Max<int>(Order1, Order2), CT>
    operator+(const Polynomial<Order1, CT> &_p1, const Polynomial<Order2, CT> &_p2);

    template <int Order1, int Order2, class CT>
    friend const Polynomial<Max<int>(Order1, Order2), CT>
    operator-(const Polynomial<Order1, CT> &_p1, const Polynomial<Order2, CT> &_p2);

    template <int Order1, int Order2, class CT>
    friend const Polynomial<Order1 + Order2 - 1, CT>
    operator*(const Polynomial<Order1, CT> &_p1, const Polynomial<Order2, CT> &_p2);

  ///For opertation 'multiply_overflow', all p-th (p>N) terms of the result will be neglected.
    template <int Ord, class CT>
    friend const Polynomial<Ord, CT>
    multiply_overflow(const Polynomial<Ord, CT> &_p1, const Polynomial<Ord, CT> &_p2);


    template <int Ord, class CT>
    friend const Polynomial<Ord, CT>
    operator*(const Polynomial<Ord, CT> &_p, const Real &_x);

    const Polynomial<Order, CoefType> operator-() const;
    ///
    /**
     * Useful Math Tools.
     */
    template <class ParaT>
    CoefType eval(const ParaT &_x) const;

    const Polynomial<Order - 1, CoefType> derivate() const;

    const Polynomial<Order + 1, CoefType> integral() const;
    ///
    /**
     * Standard Output Format.
     */
    friend std::ostream &operator<<<>(std::ostream &os, const Polynomial<Order, CoefType> &_p);
};

//=====================Useful Math Tools.=============================
template <int Order, class CoefType>
template <class ParaT>
CoefType Polynomial<Order, CoefType>::eval(const ParaT &_x) const
{
    ParaT pow_x = static_cast<ParaT>(1);
    CoefType px = Coef_[0];
    for (int i = 1; i < Order; i++)
    {
        pow_x *= _x;
        px = px + Coef_[i] * pow_x;
    };
    return px;
};

template <int Order, class CoefType>
const Polynomial<Order - 1, CoefType> Polynomial<Order, CoefType>::derivate() const
{
    Polynomial<Order - 1, CoefType> res;
    if (Order > 1)
        for (int i = 0; i < Max<int>(Order - 1, 1); i++)
            res[i] = Coef_[i + 1] * (i + 1);
    return res;
};

///
/**
     The constant term is always 0.
   */
template <int Order, class CoefType>
const Polynomial<Order + 1, CoefType> Polynomial<Order, CoefType>::integral() const
{
    Polynomial<Order + 1, CoefType> res;
    for (int i = 1; i <= Order; i++)
        res[i] = Coef_[i - 1] / i;
    return res;
};

//=====================Elementary Operations=============================
template <int Order1, int Order2, class CoefType>
const Polynomial<Max<int>(Order1, Order2), CoefType>
operator+(const Polynomial<Order1, CoefType> &_p1, const Polynomial<Order2, CoefType> &_p2)
{
    Polynomial<Max<int>(Order1, Order2), CoefType> res;
    if (Order1 >= Order2)
    {
        int i = 0;
        for (; i < Order1 + Order2 - Max<int>(Order1, Order2); i++)
            res[i] = _p1[i] + _p2[i];
        for (; i < Order1; i++)
            res[i] = _p1[i];
        return res;
    }
    else
        return _p2 + _p1;
};

template <int Order1, int Order2, class CT>
const Polynomial<Order1 + Order2 - 1, CT>
operator*(const Polynomial<Order1, CT> &_p1, const Polynomial<Order2, CT> &_p2)
{
    Polynomial<Order1 + Order2 - 1, CT> res;
    for (int i = 0; i < Order1; i++)
        for (int j = 0; j < Order2; j++)
            res[i + j] = res[i + j] + _p1[i] * _p2[j];
    return res;
};

template <int Ord, class CT>
const Polynomial<Ord, CT>
multiply_overflow(const Polynomial<Ord, CT> &_p1, const Polynomial<Ord, CT> &_p2)
{
    Polynomial<Ord, CT> res;
    for (int i = 0; i < Ord; i++)
        for (int j = 0; (i + j < Ord); j++)
            res[i + j] = res[i + j] + _p1[i] * _p2[j];
    return res;
}

template <int Order, class CoefType>
const Polynomial<Order, CoefType>
operator*(const Polynomial<Order, CoefType> &_p, const Real &_x)
{
    Polynomial<Order, CoefType> res;
    for (int i = 0; i < Order; i++)
        res[i] = _p[i] * _x;
    return res;
};

template <int Order, class CoefType>
const Polynomial<Order, CoefType> Polynomial<Order, CoefType>::operator-() const
{
    return (*this) * (-1);
};

template <int Order1, int Order2, class CoefType>
const Polynomial<Max<int>(Order1, Order2), CoefType>
operator-(const Polynomial<Order1, CoefType> &_p1, const Polynomial<Order2, CoefType> &_p2)
{
    return _p1 + (-_p2);
};

//=====================Standard Output Format=============================
template <int Order, class CoefType>
std::ostream &operator<<(std::ostream &os, const Polynomial<Order, CoefType> &_p)
{
    os << "px = ";
    if (Order == 0)
    {
        os << "0 ";
        return os;
    }
    else
    {
        const int pDeg = Order - 1;
        os << _p[pDeg] << "*x.^" << pDeg;
        for (int i = pDeg - 1; i >= 0; i--)
            os << " + " << _p[i] << "*x.^" << i;
        os << " ";
        return os;
    }
};

#else
//do nothing
#endif
