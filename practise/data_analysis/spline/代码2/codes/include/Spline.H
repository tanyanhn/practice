/**
 * @file Spline.H
 * @brief 一个用于实现样条插值的模板类。
 * 支持 ppForm 与 cardianlBSpline。
 * @author htli (3180102114@zju.edu.cn)
 * @version 1.0
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021  linhuo2020
 * 
 */
#ifndef _PROJECT3_SPLINE_H_
#define _PROJECT3_SPLINE_H_

#include "Vec.h"
#include "Polynomial.H"
#include "NewtonInterp_Portable.H"
#include "CardinalBspline.H"
#include <fstream>
#include <string>
#include <algorithm>
#include <lapacke.h>

enum SplineType
{
    ppForm,
    cardinalB,
};

enum BCType
{
    complete,
    notAknot,
    periodic,
    middleSite,
};

template <int Dim, int Order, SplineType t>
class Spline;

//========================================================================
//========================================================================
//========================================================================
//—————————————————————————ppFormSpline--------------------------------

template <int D, int Ord>
const Spline<D, Ord, ppForm>
operator*(Spline<D, Ord, ppForm> &_spl, const Real &_x);

template <int D, int Ord>
void plotIn(const Spline<D, Ord, ppForm> &_spl, const std::string &_file, const int Num = 500);

template <int Order>
Spline<2, Order, ppForm> fitCurve(const std::vector<Vec<Real, 2>> &_KnotsInfo, BCType type = notAknot);

template <int Order>
Spline<1, Order, ppForm> interpolate(const InterpConditions &_IntpInfo, BCType type = notAknot);

template <int Dim, int Order>
class Spline<Dim, Order, ppForm>
{
public:
    using rVec = Vec<Real, Dim>;
    using T_Poly = Polynomial<Order, rVec>;

protected:
    std::vector<Real> Knots_;
    std::vector<T_Poly> Polys_;
    Real Tol = 1e-7;
    void setAll(const std::vector<T_Poly> _ps, const std::vector<Real> _knots)
    {
        Knots_ = _knots;
        Polys_ = _ps;
    };

public:

  Spline() = default;

  /// 拷贝一下起始点塞进去
  Spline(const Real &_StartKnot) { Knots_.push_back(_StartKnot); };

  /// 给定初始值
  Spline(const T_Poly &_p, const Real &_len, const Real &_StartKnot = 0.0)
    {
        Knots_.push_back(_StartKnot);
        Knots_.push_back(_StartKnot + _len);
        Polys_.push_back(_p);
    };
    ~Spline() = default;
    ///
    /**
     * Get & Set.
     */
    const std::vector<Real> &getKnots() const { return Knots_; };
    const std::vector<T_Poly> &getPolys() const { return Polys_; };

  const rVec getStartPoint() const { return Polys_[0][0]; };
    const rVec getEndPoint() const { return (Polys_.back()).eval(Knots_.back() - *(Knots_.rbegin() + 1)); };

  const bool IsEmpty() const { return (Knots_.size() < 1); };
  const bool IsKnotIncluded(Real _t) const { return (!IsEmpty()) && (_t > Knots_[0] - Tol) && (_t < Knots_.back() + Tol); };

  const int locatePiece(Real _t) const;

  ///存入的分段多项式默认参数以0开始，故内部读取时需要减去实际节点.
  const rVec operator()(Real _t) const { return (Polys_[locatePiece(_t)]).eval(_t - Knots_[locatePiece(_t)]); };

    void polycat(const T_Poly &_p, const Real _len);
    void polycat(const Spline<Dim, Order, ppForm> &_spl);
    ///
    /**
     * Useful Math Tools.
     */
    template <int D, int Ord>
    friend const Spline<D, Ord, ppForm>
    operator*(Spline<D, Ord, ppForm> &_spl, const Real &_x);

  template <int Ord>
    friend Spline<1, Ord, ppForm> interpolate(const InterpConditions &_KnotsInfo, BCType type);

  template <int Ord>
    friend Spline<2, Ord, ppForm> fitCurve(const std::vector<Vec<Real, 2>> &_KnotsInfo, BCType type);
    ///
    /**
     * Standard Output Format.
     */
    void display() const;
    template <int D, int Ord>
    friend void plotIn(const Spline<D, Ord, ppForm> &_spl, const std::string &_file, const int Num);
};

//=========================Get & Set===============================
template <int Dim, int Order>
const int Spline<Dim, Order, ppForm>::locatePiece(Real _t) const
{
    assert(IsKnotIncluded(_t));
    int num = Polys_.size();
    int left = 0, right = num - 1, mid;
    while (1)
    {
        if (left == right)
            return left;
        mid = (left + right) / 2;
        if (_t < Knots_[mid + 1])
            right = mid;
        else
            left = mid + 1;
    }
};

template <int Dim, int Order>
void Spline<Dim, Order, ppForm>::polycat(const T_Poly &_p, const Real _len)
{
    if (IsEmpty())
        Knots_.push_back(0.0);
    Knots_.push_back(Knots_.back() + _len);
    Polys_.push_back(_p);
};

template <int Dim, int Order>
void Spline<Dim, Order, ppForm>::polycat(const Spline<Dim, Order, ppForm> &_spl)
{
    const int Size = _spl.getPolys().size();
    for (int i = 0; i < Size; ++i)
        (*this).polycat(_spl.getPolys()[i], _spl.getKnots()[i + 1] - _spl.getKnots()[i]);
};

//=====================Useful Math Tools.=============================
template <int D, int Ord>
const Spline<D, Ord, ppForm>
operator*(Spline<D, Ord, ppForm> &_spl, const Real &_x)
{
    Spline<D, Ord, ppForm> res;
    const auto rv = _spl.getKnots();
    auto plys = _spl.getPolys();
    for (int i = 0; i < plys.size(); i++)
        plys[i] = plys[i] * _x;
    res.setAll(plys, rv);
    return res;
};

template <>
Spline<1, 2, ppForm> interpolate(const InterpConditions &_IntpInfo, BCType type)
{
    const RealBox KnotsInfo = _IntpInfo.getIntpInfo();
    const int numKnots = KnotsInfo.size();
    Spline<1, 2, ppForm> res(KnotsInfo[0][0]);
    for (int i = 0; i < numKnots - 1; i++)
    {
        Polynomial<2, Vec<Real, 1>> tempP;
        Real len = KnotsInfo[i + 1][0] - KnotsInfo[i][0];
        tempP[0] = KnotsInfo[i][1];
        tempP[1] = (KnotsInfo[i + 1][1] - KnotsInfo[i][1]) / len;
        res.polycat(tempP, len);
    }
    return res;
};

template <>
Spline<1, 4, ppForm> interpolate(const InterpConditions &_IntpInfo, BCType type)
{
    const RealBox KnotsInfo = _IntpInfo.getIntpInfo();
    const int numKnots = KnotsInfo.size();
    Spline<1, 4, ppForm> res(KnotsInfo[0][0]);
    // Preparation: collect knots
    const int N = KnotsInfo.size();
    std::vector<Real> knots(N);
    for (int i = 0; i < N; i++)
        knots[i] = KnotsInfo[i][0];
    //Preparation: calculate the divided table for coord x and y
    NewtonInterp xNI(_IntpInfo);
    xNI.QuickInterp(3);
    //Preparation: collect the data
    std::vector<Real> xTriT_3rdCol = xNI.getTableOfDividedDiffs().getNthCol(3);
    Real xTriT_2rdColFront = xNI.getTableOfDividedDiffs().getNthCol(2).front();
    Real xTriT_2rdColBack = xNI.getTableOfDividedDiffs().getNthCol(2).back();
    //Step1: assemble coefficent matrix for 2rd derivation {M}
    Real Coe[N * N];
    for (int i = 0; i < N * N; i++)
        Coe[i] = 0;
    //1.1 periodic conditon or notAknot Condition or Complete Condition
    if (type == periodic)
    {
        Coe[0] = 1, Coe[N - 1] = -1;
        Coe[N * (N - 1)] = 2.0 * (knots[1] - knots[0]);
        Coe[N * (N - 1) + 1] = knots[1] - knots[0];
        Coe[N * N - 2] = knots[N - 1] - knots[N - 2];
        Coe[N * N - 1] = 2 * (knots[N - 1] - knots[N - 2]);
    }
    else if (type == notAknot)
    {
        Coe[0] = knots[1] - knots[2];
        Coe[1] = knots[2] - knots[0];
        Coe[2] = knots[0] - knots[1];
        Coe[N * (N - 1) + N - 3] = knots[N - 2] - knots[N - 1];
        Coe[N * (N - 1) + N - 2] = knots[N - 1] - knots[N - 3];
        Coe[N * (N - 1) + N - 1] = knots[N - 3] - knots[N - 2];
    }
    else
    {
        Coe[0] = 2, Coe[1] = 1;
        Coe[N * (N - 1) + N - 2] = 1;
        Coe[N * (N - 1) + N - 1] = 2;
    };
    //1.2 continity condition
    for (int rowN = 1; rowN < N - 1; rowN++)
    {
        Coe[rowN * N + rowN - 1] = (knots[rowN] - knots[rowN - 1]) / (knots[rowN + 1] - knots[rowN - 1]);
        Coe[rowN * N + rowN] = 2.0;
        Coe[rowN * N + rowN + 1] = (knots[rowN + 1] - knots[rowN]) / (knots[rowN + 1] - knots[rowN - 1]);
    }
    //Step2: assemble RHS.
    Real rhs[N];
    //2.1 periodic conditon or notAknot Condition
    if (type == periodic)
    {
        rhs[0] = 0;
        rhs[N - 1] = 6.0 * (xTriT_2rdColFront - xTriT_2rdColBack);
        //2.2 continity condition
        for (int rowN = 1; rowN < N - 1; rowN++)
            rhs[rowN] = 6.0 * xTriT_3rdCol[rowN - 1];
    }
    else if (type == notAknot)
    {
        rhs[0] = 0;
        rhs[N - 1] = 0;
        //2.2 continity condition
        for (int rowN = 1; rowN < N - 1; rowN++)
            rhs[rowN] = 6.0 * xTriT_3rdCol[rowN - 1];
    }
    else
    {
        for (int rowN = 0; rowN < N; rowN++)
            rhs[rowN] = 6.0 * xTriT_3rdCol[rowN];
    };
    //Step3: Lapacke Solver.
    int ipiv[N];
    int n = N;
    int nrhs = 1;
    int lda = N;
    int ldb = 1;
    auto info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, Coe, lda, ipiv, rhs, ldb);
    assert(info == 0);
    std::vector<Vec<Real, 1>> Knots2rdDer(N);
    for (int i = 0; i < N; i++)
        Knots2rdDer[i] = {rhs[i]};
    for (int i = 0; i < N - 1; i++)
    {
        Real len = knots[i + 1] - knots[i];
        Polynomial<2, Vec<Real, 1>> tempP;
        tempP[0] = Knots2rdDer[i];
        tempP[1] = (Knots2rdDer[i + 1] - Knots2rdDer[i]) / len;
        Polynomial<4, Vec<Real, 1>> result = tempP.integral().integral();
        result[0] = KnotsInfo[i][1];
        Vec<Real, 1> LinearCoe = KnotsInfo[i + 1][1] / len;
        LinearCoe = LinearCoe - result.eval(len) / len;
        result[1] = LinearCoe;
        res.polycat(result, len);
    }

    return res;
};

template <>
Spline<2, 2, ppForm> fitCurve(const std::vector<Vec<Real, 2>> &_KnotsInfo, BCType type
{
    const int numKnots = _KnotsInfo.size();
    Spline<2, 2, ppForm> res;
    for (int i = 0; i < numKnots - 1; i++)
    {
        Polynomial<2, Vec<Real, 2>> tempP;
        Real len = norm(_KnotsInfo[i + 1] - _KnotsInfo[i], 2);
        tempP[0] = _KnotsInfo[i];
        tempP[1] = (_KnotsInfo[i + 1] - _KnotsInfo[i]) / len;
        res.polycat(tempP, len);
    }
    return res;
};

template <>
Spline<2, 4, ppForm> fitCurve(const std::vector<Vec<Real, 2>> &_KnotsInfo, BCType type)
{
    Spline<2, 4, ppForm> res;
    // For type = periodic or notAKnot
    if (type != complete)
    {
        // Preparation: calculate the accumulated chordal length
        const int N = _KnotsInfo.size();
        std::vector<Real> knots(N);
        knots[0] = 0;
        for (int i = 1; i < N; i++)
            knots[i] = knots[i - 1] + norm(_KnotsInfo[i] - _KnotsInfo[i - 1], 2);
        //Preparation: calculate the divided table for coord x and y
        RealBox xBox, yBox;
        for (int i = 0; i < N; i++)
        {
            xBox.push_back({knots[i], _KnotsInfo[i][0]});
            yBox.push_back({knots[i], _KnotsInfo[i][1]});
        }
        InterpConditions xIC(xBox), yIC(yBox);
        NewtonInterp xNI(xIC), yNI(yIC);
        xNI.QuickInterp(3), yNI.QuickInterp(3);
        //Preparation: collect the data
        std::vector<Real> xTriT_3rdCol = xNI.getTableOfDividedDiffs().getNthCol(3);
        std::vector<Real> yTriT_3rdCol = yNI.getTableOfDividedDiffs().getNthCol(3);
        Real xTriT_2rdColFront = xNI.getTableOfDividedDiffs().getNthCol(2).front();
        Real xTriT_2rdColBack = xNI.getTableOfDividedDiffs().getNthCol(2).back();
        Real yTriT_2rdColFront = yNI.getTableOfDividedDiffs().getNthCol(2).front();
        Real yTriT_2rdColBack = yNI.getTableOfDividedDiffs().getNthCol(2).back();
        //Step1: assemble coefficent matrix for 2rd derivation {M}
        Real Coe[N * N];
        for (int i = 0; i < N * N; i++)
            Coe[i] = 0;
        //1.1 periodic conditon or notAknot Condition
        if (type == periodic)
        {
            Coe[0] = 1, Coe[N - 1] = -1;
            Coe[N * (N - 1)] = 2.0 * (knots[1] - knots[0]);
            Coe[N * (N - 1) + 1] = knots[1] - knots[0];
            Coe[N * N - 2] = knots[N - 1] - knots[N - 2];
            Coe[N * N - 1] = 2 * (knots[N - 1] - knots[N - 2]);
        }
        else if (type == notAknot)
        {
            Coe[0] = knots[1] - knots[2];
            Coe[1] = knots[2] - knots[0];
            Coe[2] = knots[0] - knots[1];
            Coe[N * (N - 1) + N - 3] = knots[N - 2] - knots[N - 1];
            Coe[N * (N - 1) + N - 2] = knots[N - 1] - knots[N - 3];
            Coe[N * (N - 1) + N - 1] = knots[N - 3] - knots[N - 2];
        };
        //1.2 continity condition
        for (int rowN = 1; rowN < N - 1; rowN++)
        {
            Coe[rowN * N + rowN - 1] = (knots[rowN] - knots[rowN - 1]) / (knots[rowN + 1] - knots[rowN - 1]);
            Coe[rowN * N + rowN] = 2.0;
            Coe[rowN * N + rowN + 1] = (knots[rowN + 1] - knots[rowN]) / (knots[rowN + 1] - knots[rowN - 1]);
        }
        //Step2: assemble RHS.
        Real rhs[2 * N];
        //2.1 periodic conditon or notAknot Condition
        if (type == periodic)
        {
            rhs[0] = 0, rhs[1] = 0;
            rhs[2 * N - 2] = 6.0 * (xTriT_2rdColFront - xTriT_2rdColBack);
            rhs[2 * N - 1] = 6.0 * (yTriT_2rdColFront - yTriT_2rdColBack);
        }
        else if (type == notAknot)
        {
            rhs[0] = 0, rhs[1] = 0;
            rhs[2 * N - 2] = 0, rhs[2 * N - 1] = 0;
        };
        //2.2 continity condition
        for (int rowN = 1; rowN < N - 1; rowN++)
        {
            rhs[2 * rowN] = 6.0 * xTriT_3rdCol[rowN - 1];
            rhs[2 * rowN + 1] = 6.0 * yTriT_3rdCol[rowN - 1];
        }
        //Step3: Lapacke Solver.
        int ipiv[N];
        int n = N;
        int nrhs = 2;
        int lda = N;
        int ldb = 2;
        auto info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, Coe, lda, ipiv, rhs, ldb);
        assert(info == 0);
        std::vector<Vec<Real, 2>> Knots2rdDer(N);
        for (int i = 0; i < N; i++)
            Knots2rdDer[i] = {rhs[2 * i], rhs[2 * i + 1]};
        for (int i = 0; i < N - 1; i++)
        {
            Real len = knots[i + 1] - knots[i];
            Polynomial<2, Vec<Real, 2>> tempP;
            tempP[0] = Knots2rdDer[i];
            tempP[1] = (Knots2rdDer[i + 1] - Knots2rdDer[i]) / len;
            Polynomial<4, Vec<Real, 2>> result = tempP.integral().integral();
            result[0] = _KnotsInfo[i];
            Vec<Real, 2> LinearCoe = (_KnotsInfo[i + 1] - result.eval(len)) / len;
            result[1] = LinearCoe;
            res.polycat(result, len);
        }
        return res;
    }
    // For type = complete, we assume the two additional derivation conditions
    // are at the end of the input.
    else
    {
        assert(type == complete);
        // Preparation: calculate the accumulated chordal length
        const int N = _KnotsInfo.size() - 2;
        std::vector<Real> knots(N);
        knots[0] = 0;
        for (int i = 1; i < N; i++)
            knots[i] = knots[i - 1] + norm(_KnotsInfo[i] - _KnotsInfo[i - 1], 2);
        //Preparation: calculate the divided table for coord x and y
        RealBox xBox, yBox;
        xBox.push_back({knots[0], _KnotsInfo[0][0], _KnotsInfo[N][0]});
        yBox.push_back({knots[0], _KnotsInfo[0][1], _KnotsInfo[N][1]});
        for (int i = 1; i < N - 1; i++)
        {
            xBox.push_back({knots[i], _KnotsInfo[i][0]});
            yBox.push_back({knots[i], _KnotsInfo[i][1]});
        }
        xBox.push_back({knots[N - 1], _KnotsInfo[N - 1][0], _KnotsInfo[N + 1][0]});
        yBox.push_back({knots[N - 1], _KnotsInfo[N - 1][1], _KnotsInfo[N + 1][1]});
        InterpConditions xIC(xBox), yIC(yBox);
        NewtonInterp xNI(xIC), yNI(yIC);
        xNI.QuickInterp(3), yNI.QuickInterp(3);
        //Preparation: collect the data
        std::vector<Real> xTriT_3rdCol = xNI.getTableOfDividedDiffs().getNthCol(3);
        std::vector<Real> yTriT_3rdCol = yNI.getTableOfDividedDiffs().getNthCol(3);
        //Step1: assemble coefficent matrix for 2rd derivation {M}
        Real Coe[N * N];
        for (int i = 0; i < N * N; i++)
            Coe[i] = 0;
        //1.1 complete conditon
        Coe[0] = 2, Coe[1] = 1;
        Coe[N * (N - 1) + N - 2] = 1;
        Coe[N * (N - 1) + N - 1] = 2;
        //1.2 continity condition
        for (int rowN = 1; rowN < N - 1; rowN++)
        {
            Coe[rowN * N + rowN - 1] = (knots[rowN] - knots[rowN - 1]) / (knots[rowN + 1] - knots[rowN - 1]);
            Coe[rowN * N + rowN] = 2.0;
            Coe[rowN * N + rowN + 1] = (knots[rowN + 1] - knots[rowN]) / (knots[rowN + 1] - knots[rowN - 1]);
        }
        //Step2: assemble RHS.
        Real rhs[2 * N];
        //2.1 & 2.2 complete conditon and continity condition
        for (int rowN = 0; rowN < N; rowN++)
        {
            rhs[2 * rowN] = 6.0 * xTriT_3rdCol[rowN];
            rhs[2 * rowN + 1] = 6.0 * yTriT_3rdCol[rowN];
        }
        //Step3: Lapacke Solver.
        int ipiv[N];
        int n = N;
        int nrhs = 2;
        int lda = N;
        int ldb = 2;
        auto info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, Coe, lda, ipiv, rhs, ldb);
        assert(info == 0);
        std::vector<Vec<Real, 2>> Knots2rdDer(N);
        for (int i = 0; i < N; i++)
            Knots2rdDer[i] = {rhs[2 * i], rhs[2 * i + 1]};
        for (int i = 0; i < N - 1; i++)
        {
            Real len = knots[i + 1] - knots[i];
            Polynomial<2, Vec<Real, 2>> tempP;
            tempP[0] = Knots2rdDer[i];
            tempP[1] = (Knots2rdDer[i + 1] - Knots2rdDer[i]) / len;
            Polynomial<4, Vec<Real, 2>> result = tempP.integral().integral();
            result[0] = _KnotsInfo[i];
            Vec<Real, 2> LinearCoe = (_KnotsInfo[i + 1] - result.eval(len)) / len;
            result[1] = LinearCoe;
            res.polycat(result, len);
        }
        return res;
    };
};

//=====================Standard Output Format=============================
template <int Dim, int Order>
void Spline<Dim, Order, ppForm>::display() const
{
    const int Size = Polys_.size();
    for (int i = 0; i < Size; i++)
        std::cout << i + 1 << " of " << Size
                  << " : (" << Knots_[i] << "," << Knots_[i + 1] << "), " << Polys_[i] << '\n';
};

template <int D, int Ord>
void plotIn(const Spline<D, Ord, ppForm> &_spl, const std::string &_file, const int Num)
{
    const auto knots = _spl.getKnots();
    std::ofstream os(_file);
    const Real h = (knots.back() - knots[0]) / Num;
    Real t = knots[0];
    // os<<"figure(1);\n";
    os << "t = [";
    std::vector<Vec<Real, D>> knotInfo(Num + 1);
    for (int i = 0; i <= Num; i++)
    {
        os << t << ",";
        knotInfo[i] = _spl(t);
        t += h;
    }
    os << "];\n";
    for (int i = 1; i <= D; i++)
    {
        os << "x_" << i << " = [";
        for (int j = 0; j <= Num; j++)
            os << knotInfo[j][i - 1] << ",";
        os << "];\n";
    }
    if (D == 1)
        os << "h=plot(t,x_1);";
    else if (D == 2)
        os << "h=plot(x_1,x_2);";
    // os << 'hold on;\n'<<"saveas(1,\""<<_file<<".png\");"<<'\n'<<"clf(1)";
    os.close();
};

//========================================================================
//========================================================================
//========================================================================
//—————————————————————————cardinalBspline--------------------------------

template <int Order>
Spline<1, Order, cardinalB> interpolate(const InterpConditions &_IntpInfo, BCType type, SplineType t);
template <int Ord>
void plotIn(const Spline<1, Ord, cardinalB> &_spl, const std::string &_file, const int Num = 500);

template <int Order>
class Spline<1, Order, cardinalB>
{
protected:
    int StartKnot_;
    int NumKnots_;
    std::vector<Real> Coefs_;
    Real Tol = 1e-6;

public:
    Spline() = default;
    ~Spline() = default;
    ///
    /**
     * Get & Set.
     */
    const std::vector<Real> &getCoefs() const { return Coefs_; };
    const bool IsEmpty() const { return NumKnots_ < 1; };
    const bool IsKnotIncluded(Real _t) const { return (!IsEmpty()) && (_t > StartKnot_ - Tol) && (_t < StartKnot_ + NumKnots_ - 1 + Tol); };
    //返回区间index( 从0开始 )
    const int locatePiece(Real _t) const;
    const Real operator()(Real _t) const;
    const std::vector<Real> getKnots() const
    {
        std::vector<Real> res;
        for (int k = StartKnot_; k < NumKnots_ + StartKnot_; k++)
            res.push_back(k);
        return res;
    };
    void setInfo(int _StartKnot, int _NumKnots, std::vector<Real> _Coefs)
    {
        StartKnot_ = _StartKnot;
        NumKnots_ = _NumKnots;
        Coefs_ = _Coefs;
    };
    ///
    /**
     * Useful Math Tools.
     */
    template <int Ord>
    friend Spline<1, Ord, cardinalB> interpolate(const InterpConditions &_KnotsInfo, BCType type, SplineType t);
    ///
    /**
     * Standard Output Format.
     */
    template <int Ord>
    friend void plotIn(const Spline<1, Ord, cardinalB> &_spl, const std::string &_file, const int Num);
};

//=============================Get & Set==================================
template <int Order>
const int Spline<1, Order, cardinalB>::locatePiece(Real _t) const
{
    assert(IsKnotIncluded(_t));
    int left = 0, right = NumKnots_ - 1, mid;
    while (1)
    {
        if (left == right)
            return left;
        mid = (left + right) / 2;
        if (_t < StartKnot_ + mid + 1)
            right = mid;
        else
            left = mid + 1;
    }
};

template <int Ord>
const Real Spline<1, Ord, cardinalB>::operator()(Real _t) const
{
    const int Order = Ord - 1; //Order为数学意义下多项式的次数
    const int tIndex = locatePiece(_t);
    const int EndKnot = StartKnot_ + NumKnots_ - 1;
    Real temp = 0;
    if (_t >= EndKnot)
    {
        for (int i = 1; i <= Order; i++)
            temp += Coefs_[tIndex + Order - i] * CardBSpline<Order>(StartKnot_ + tIndex - i + 1, _t);
        return temp;
    }
    for (int i = 0; i <= Order; i++)
        temp += Coefs_[tIndex + Order - i] * CardBSpline<Order>(StartKnot_ + tIndex - i + 1, _t);
    return temp;
};

//=====================Useful Math Tools.====================================
template <>
Spline<1, 3, cardinalB> interpolate(const InterpConditions &_IntpInfo, BCType type, SplineType t)
{
    assert(t == cardinalB);
    Spline<1, 3, cardinalB> res;
    const RealBox KnotsInfo = _IntpInfo.getIntpInfo();
    if (type == middleSite)
    {
        const int N = KnotsInfo.size() - 1;
        const int StartKnot = KnotsInfo[0][0];
        //Step1: assemble coefficent matrix for 2rd derivation {M}
        Real Coe[(N + 1) * (N + 1)];
        for (int i = 0; i < (N + 1) * (N + 1); i++)
            Coe[i] = 0;
        //1.1 middleSite conditon
        Coe[0] = 1, Coe[1] = 1;
        Coe[(N + 1) * (N + 1) - 2] = 1, Coe[(N + 1) * (N + 1) - 1] = 1;
        //1.2 continity condition
        for (int rowN = 1; rowN < N; rowN++)
        {
            Coe[rowN * (N + 1) + rowN - 1] = 1.0;
            Coe[rowN * (N + 1) + rowN] = 6.0;
            Coe[rowN * (N + 1) + rowN + 1] = 1.0;
        }
        //Step2: assemble RHS.
        Real rhs[N + 1];
        rhs[0] = 2.0 * KnotsInfo[0][1], rhs[N] = 2.0 * KnotsInfo.back()[1];
        for (int rowN = 1; rowN < N; rowN++)
            rhs[rowN] = 8.0 * KnotsInfo[rowN][1];
        //Step3: Lapacke Solver.
        int ipiv[N + 1];
        int n = N + 1;
        int nrhs = 1;
        int lda = N + 1;
        int ldb = 1;
        auto info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, Coe, lda, ipiv, rhs, ldb);
        assert(info == 0);
        std::vector<Real> Coefs(N + 1);
        for (int i = 0; i < N + 1; i++)
            Coefs[i] = rhs[i];
        res.setInfo(StartKnot, N, Coefs);
    };
    return res;
};

template <>
Spline<1, 4, cardinalB> interpolate(const InterpConditions &_IntpInfo, BCType type, SplineType t)
{
    assert(t == cardinalB);
    Spline<1, 4, cardinalB> res;
    const RealBox KnotsInfo = _IntpInfo.getIntpInfo();

    if (type == complete)
    {
        const int N = KnotsInfo.size();
        const int StartKnot = KnotsInfo[0][0];
        //Step1: assemble coefficent matrix
        Real Coe[(N + 2) * (N + 2)];
        for (int i = 0; i < (N + 2) * (N + 2); i++)
            Coe[i] = 0;
        //1.1 complete conditon
        Coe[0] = 1, Coe[2] = -1;
        Coe[(N + 2) * (N + 2) - 3] = 1, Coe[(N + 2) * (N + 2) - 1] = -1;
        //1.2 continity condition
        for (int rowN = 1; rowN < N + 1; rowN++)
        {
            Coe[rowN * (N + 2) + rowN - 1] = 1.0;
            Coe[rowN * (N + 2) + rowN] = 4.0;
            Coe[rowN * (N + 2) + rowN + 1] = 1.0;
        }
        //Step2: assemble RHS.
        Real rhs[N + 2];
        rhs[0] = -2.0 * KnotsInfo[0][2];
        for (int rowN = 0; rowN < N; rowN++)
            rhs[rowN + 1] = 6.0 * KnotsInfo[rowN][1];
        rhs[N + 1] = -2.0 * KnotsInfo[N - 1][2];
        //Step3: Lapacke Solver.
        int ipiv[N + 2];
        int n = N + 2;
        int nrhs = 1;
        int lda = N + 2;
        int ldb = 1;
        auto info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, Coe, lda, ipiv, rhs, ldb);
        assert(info == 0);
        std::vector<Real> Coefs(N + 2);
        for (int i = 0; i < N + 2; i++)
            Coefs[i] = rhs[i];
        res.setInfo(StartKnot, N, Coefs);
    };
    return res;
};


//=====================Standard Output Format=============================
template <int Ord>
void plotIn(const Spline<1, Ord, cardinalB> &_spl, const std::string &_file, const int Num)
{
    const auto knots = _spl.getKnots();
    std::ofstream os(_file);
    const Real h = (knots.back() - knots[0]) / Num;
    Real t = knots[0];
    os << "t = [";
    std::vector<Real> knotInfo(Num + 1);
    for (int i = 0; i <= Num; i++)
    {
        os << t << ",";
        knotInfo[i] = _spl(t);
        t += h;
    }
    os << "];\n";
    os << "x_1 = [";
    for (int j = 0; j <= Num; j++)
        os << knotInfo[j] << ",";
    os << "];\n";
    os << "h=plot(t,x_1);\n";
    os.close();
};


#else
//do nothing
#endif
