#ifndef _SPLIE_BUILDER_HPP_
#define _SPLIE_BUILDER_HPP_

#include "Spline.hpp"
#include "SplineCondition.hpp"
#include "myLapack.hpp"
#include "Vec.h"

namespace SplineBuilder {

    class SplineHelper {

    public:
    
        static Spline<0, 3, SplineType::ppForm> _build_by_f_m(int N, const std::vector<Real> &t, Real *f, Real *m) { // all 0-index
            line<0, 3, SplineType::ppForm> spl;
            spl.N = N;
            spl.t.assign(t.begin() + 1, t.begin() + N + 1);
            spl.piece.reserve(N - 1);
            for (int i = 0; i < N - 1; ++i) {
                Real len = spl.t[i + 1] - spl.t[i];
                Real u1 = f[i + 1] - f[i] - m[i] * len;
                Real u2 = m[i + 1] - m[i];
                Real a2 = (3 * u1 - len * u2) / (len * len);
                Real a3 = (len * u2 - 2 * u1) / (len * len * len);
                spl.piece.push_back(Polynomial<3, Real>{f[i], m[i], a2, a3});
            }
            return spl;
        }

    };

    template<int Dim, int Order, SplineType st, BCType bc>
    class Interpolate;

    template<int Dim>
    class Interpolate<Dim, 3, SplineType::ppForm, BCType::complete> {
    public:
        static Spline<Dim, 3, SplineType::ppForm> create(const SplineCondition<Vec<Dim, Real>> &cond) {
            Spline<Dim, 3, SplineType::ppForm> ret;
            if (cond.N < 2) return ret;

            int N = cond.N;
            int _N = N - 2, KL = 1, KU = 1, NRHS = Dim;
            Real *AB = new Real[4 * _N];
            int LDAB = 4;
            int *IPIV = new int[_N];
            Real *B = new Real[N * Dim];
            int LDB = N;
            int INFO;

            Real *f_com = new Real[N];

            for (int i = 0; i < Dim; ++i) {
                B[i * N] = cond.getC(1, 1)[i];
                B[(i + 1) * N - 1] = cond.getC(N, 1)[i];
            }

            Real *mu = new Real[N + 1];
            Real *lam = new Real[N + 1];

            if (N >= 3) {
                for (int i = 2; i < N; ++i) {
                    Real tl = cond.t[i - 1], tm = cond.t[i], tr = cond.t[i + 1];
                    mu[i] = (tm - tl) / (tr - tl);
                    lam[i] = (tr - tm) / (tr - tl);
                }
            }

            if (N == 3) {
                for (int i = 0; i < Dim; ++i) {
                    Real t1 = cond.t[1], t2 = cond.t[2], t3 = cond.t[3];
                    Real f1 = cond.c[1][0][i], f2 = cond.c[2][0][i], f3 = cond.c[3][0][i];
                    Real fir = (f2 - f1) / (t2 - t1);
                    Real sec = (f3 - f2) / (t3 - t2);
                    Real m1 = B[i * N], m3 = B[(i + 1) * N - 1];
                    Real m2 = ((lam[2] * fir + mu[2] * sec) * 3 - lam[2] * m1 - mu[2] * m3) / 2;
                    B[i * N + 1] = m2;
                }
            }

            if (N > 3) {
                AB[2 * 4 - 3] = mu[2];
                AB[2 * 4 - 6] = 2;
                for (int i = 3; i < N - 1; ++i) {
                    AB[i * 4 - 3] = mu[i];
                    AB[i * 4 - 6] = 2;
                    AB[i * 4 - 9] = lam[i];
                }
                AB[(N - 1) * 4 - 6] = 2;
                AB[(N - 1) * 4 - 9] = lam[N - 1];

                for (int k = 0; k < Dim; ++k) {
                    Real *L = B + (k * N) - 1;
                    for (int i = 2; i < N; ++i) {
                        Real tl = cond.t[i - 1], tm = cond.t[i], tr = cond.t[i + 1];
                        Real fl = cond.c[i - 1][0][k];
                        Real fm = cond.c[i][0][k];
                        Real fr = cond.c[i + 1][0][k];
                        L[i] = ((fm - fl) / (tm - tl) * lam[i] + (fr - fm) / (tr - tm) * mu[i]) * 3;
                    }
                    L[2] -= lam[2] * L[1];
                    L[N - 1] -= mu[N - 1] * L[N];
                }

                // now AB and B are set, solve the system!

                gbsv<Real>(&_N, &KL, &KU, &NRHS, AB, &LDAB, IPIV, B + 1, &LDB, &INFO);
            }

            ret.N = N;
            ret.t.resize(N);
            ret.piece.resize(N - 1);
            for (int j = 1; j <= N; ++j) ret.t[j - 1] = cond.getT(j);
            for (int i = 0; i < Dim; ++i) {
                for (int j = 1; j <= N; ++j) f_com[j - 1] = cond.getC(j, 0)[i];
                Spline<0, 3, SplineType::ppForm> spl = SplineHelper::_build_by_f_m(N, cond.t, f_com, B + (i * N));
                for (int j = 0; j < N - 1; ++j) {
                    for (int k = 0; k <= 3; ++k) ret.piece[j][k][i] = spl.piece[j][k]; // ret.piece[j][k][i]
                }
            }

            delete[] AB;
            delete[] IPIV;
            delete[] B;
            delete[] f_com;
            delete[] mu;
            delete[] lam;

            return ret;
        }
    };

    template<int Dim>
    class Interpolate<Dim, 3, SplineType::ppForm, BCType::notAknot> {
    public:
        static Spline<Dim, 3, SplineType::ppForm> create(const SplineCondition<Vec<Dim, Real>> &cond) {
            Spline<Dim, 3, SplineType::ppForm> ret;
            if (cond.N <= 3) return ret;

            int N = cond.N;
            int _N = N - 2, KL = 1, KU = 1, NRHS = Dim;
            Real *AB = new Real[4 * _N];
            int LDAB = 4;
            int *IPIV = new int[_N];
            Real *B = new Real[N * Dim];
            int LDB = N;
            int INFO;

            Real *f_com = new Real[N];

            Real *mu = new Real[N + 1];
            Real *lam = new Real[N + 1];

            for (int i = 2; i < N; ++i) {
                Real tl = cond.t[i - 1], tm = cond.t[i], tr = cond.t[i + 1];
                mu[i] = (tm - tl) / (tr - tl);
                lam[i] = (tr - tm) / (tr - tl);
            }

            Real l1 = cond.t[2] - cond.t[1], l2 = cond.t[3] - cond.t[2];
            Real ln_2 = cond.t[N - 1] - cond.t[N - 2];
            Real ln_1 = cond.t[N] - cond.t[N - 1];
            AB[2 * 4 - 3] = l1 / l2;
            AB[2 * 4 - 6] = 1 + l1 / l2;
            for (int i = 3; i < N - 1; ++i) {
                AB[i * 4 - 3] = mu[i];
                AB[i * 4 - 6] = 2;
                AB[i * 4 - 9] = lam[i];
            }
            AB[(N - 1) * 4 - 6] = 1 + ln_1 / ln_2;
            AB[(N - 1) * 4 - 9] = ln_1 / ln_2;

            for (int k = 0; k < Dim; ++k) {
                Real *L = B + (k * N) - 1;
                for (int i = 2; i < N; ++i) {
                    Real tl = cond.t[i - 1], tm = cond.t[i], tr = cond.t[i + 1];
                    Real fl = cond.c[i - 1][0][k];
                    Real fm = cond.c[i][0][k];
                    Real fr = cond.c[i + 1][0][k];
                    L[i] = ((fm - fl) / (tm - tl) * lam[i] + (fr - fm) / (tr - tm) * mu[i]) * 3;
                }
                Real K1 = (cond.c[2][0][k] - cond.c[1][0][k]) / l1;
                Real K2 = (cond.c[3][0][k] - cond.c[2][0][k]) / l2;
                Real Kn_1 = (cond.c[N][0][k] - cond.c[N - 1][0][k]) / ln_1;
                Real Kn_2 = (cond.c[N - 1][0][k] - cond.c[N - 2][0][k]) / ln_2;
                L[2] = lam[2] * K1 + K2 * (mu[2] + 2 * l1 / l2);
                L[N - 1] = mu[N - 1] * Kn_1 + Kn_2 * (lam[N - 1] + 2 * ln_1 / ln_2);
                L[1] = 3 * lam[2] * K1 + 3 * mu[2] * K2;
                L[N] = 3 * lam[N - 1] * Kn_2 + 3 * mu[N - 1] * Kn_1;
            }

            // now AB and B are set, solve the system!

            gbsv<Real>(&_N, &KL, &KU, &NRHS, AB, &LDAB, IPIV, B + 1, &LDB, &INFO);

            for (int k = 0; k < Dim; ++k) {
                Real *L = B + (k * N - 1);
                L[1] = (L[1] - 2 * L[2] - mu[2] * L[3]) / lam[2];
                L[N] = (L[N] - 2 * L[N - 1] - lam[N - 1] * L[N - 2]) / mu[N - 1];
            }

            ret.N = N;
            ret.t.resize(N);
            ret.piece.resize(N - 1);
            for (int j = 1; j <= N; ++j) ret.t[j - 1] = cond.getT(j);
            for (int i = 0; i < Dim; ++i) {
                for (int j = 1; j <= N; ++j) f_com[j - 1] = cond.getC(j, 0)[i];
                Spline<0, 3, SplineType::ppForm> spl = SplineHelper::_build_by_f_m(N, cond.t, f_com, B + (i * N));
                for (int j = 0; j < N - 1; ++j) {
                    for (int k = 0; k <= 3; ++k) ret.piece[j][k][i] = spl.piece[j][k]; // ret.piece[j][k][i]
                }
            }

            delete[] AB;
            delete[] IPIV;
            delete[] B;
            delete[] f_com;
            delete[] mu;
            delete[] lam;

            return ret;
        }
    };

    template<int Dim>
    class Interpolate<Dim, 3, SplineType::ppForm, BCType::periodic> {
    public:
        static Spline<Dim, 3, SplineType::ppForm> create(const SplineCondition<Vec<Dim, Real>> &cond) {
            Spline<Dim, 3, SplineType::ppForm> ret;
            if (cond.N < 2) return ret;

            if (cond.N == 2) {
                ret.N = 2;
                ret.t.resize(2);
                ret.t[0] = ret.t[1] = cond.t[1];
                ret.piece.push_back(Polynomial<3, Vec<Dim, Real>>{cond.t[1]});
                return ret;
            }

            int N = cond.N;
            int NRHS = Dim;
            Real *A = new Real[N * N]();
            int LDA = N;
            int *IPIV = new int[N];
            Real *B = new Real[NRHS * N];
            int LDB = N;
            int INFO;

            Real *f_com = new Real[N + 1];

            Real *mu = new Real[N + 1];
            Real *lam = new Real[N + 1];
            Real *Ks = new Real[N + 1];

            for (int i = 2; i < N; ++i) {
                Real tl = cond.t[i - 1], tm = cond.t[i], tr = cond.t[i + 1];
                mu[i] = (tm - tl) / (tr - tl);
                lam[i] = (tr - tm) / (tr - tl);
            } 

            Real l1 = cond.t[2] - cond.t[1];
            Real l2 = cond.t[3] - cond.t[2];
            Real ln_1 = cond.t[N] - cond.t[N - 1];
            Real ln_2 = cond.t[N - 1] - cond.t[N - 2];
            
            {
                A[0] = 2 * ln_1 + 2 * l1;
                A[N] = ln_1;
                A[(N - 2) * N] = l1;

                for (int i = 2; i < N; ++i) {
                    A[(i - 2) * N + (i - 1)] = lam[i];
                    A[(i - 1) * N + (i - 1)] = 2;
                    A[(i) * N + (i - 1)] = mu[i];
                }

                A[N * N - 1] = 2 * ln_1 + 2 * l1;
                A[(N - 1) * N - 1] = l1;
                A[2 * N - 1] = ln_1;
            }

            for (int k = 0; k < Dim; ++k) {
                Real *L = B + k * N - 1;
                for (int i = 1; i < N; ++i) f_com[i] = cond.c[i][0][k];
                f_com[N] = f_com[1];
                for (int i = 1; i < N; ++i) {
                    Ks[i] = (f_com[i + 1] - f_com[i]) / (cond.t[i + 1] - cond.t[i]);
                }
                L[1] = L[N] = 3 * ln_1 * Ks[1] + 3 * l1 * Ks[N - 1];
                for (int i = 2; i < N; ++i) {
                    L[i] = 3 * lam[i] * Ks[i - 1] + 3 * mu[i] * Ks[i];
                }
            }

            gesv<Real>(&N, &NRHS, A, &LDA, IPIV, B, &LDB, &INFO);

            ret.N = N;
            ret.t.resize(N);
            ret.piece.resize(N - 1);
            for (int j = 1; j <= N; ++j) ret.t[j - 1] = cond.getT(j);
            for (int i = 0; i < Dim; ++i) {
                for (int j = 1; j < N; ++j) f_com[j - 1] = cond.getC(j, 0)[i];
                f_com[N - 1] = f_com[0];
                Spline<0, 3, SplineType::ppForm> spl = SplineHelper::_build_by_f_m(N, cond.t, f_com, B + (i * N));
                for (int j = 0; j < N - 1; ++j) {
                    for (int k = 0; k <= 3; ++k) ret.piece[j][k][i] = spl.piece[j][k]; // ret.piece[j][k][i]
                }
            } 

            delete[] A;
            delete[] IPIV;
            delete[] B;
            delete[] f_com;
            delete[] mu;
            delete[] lam;
            delete[] Ks;

            return ret;
        } 
    };

    template<int Dim>
    class Interpolate<Dim, 1, SplineType::ppForm, BCType::linear> {
    public:
        static Spline<Dim, 1, SplineType::ppForm> create(const SplineCondition<Vec<Dim, Real>> &cond) {
            Spline<Dim, 1, SplineType::ppForm> ret;
            int N = cond.N;
            ret.N = N;
            ret.t.assign(cond.t.begin() + 1, cond.t.begin() + N + 1);

            if (cond.N < 2) return ret;

            ret.piece.reserve(N - 1);
            for (int i = 1; i < N; ++i) {
                Real ti = cond.t[i], tn = cond.t[i + 1];
                auto fi = cond.c[i][0], fn = cond.c[i + 1][0];
                ret.piece.push_back(Polynomial<1, Vec<Dim, Real>>{fi, (fn - fi) / (tn - ti)});
            }

            return ret;
        }
    };

    template<int Dim>
    class Interpolate<Dim, 3, SplineType::cardinalB, BCType::complete> {
    public:
        static Spline<Dim, 3, SplineType::cardinalB> create(const SplineCondition<Vec<Dim, Real>> &cond) {
            Spline<Dim, 3, SplineType::cardinalB> ret;
            if (cond.N < 2) return ret;

            int N = cond.N;
            int KL = 1, KU = 1, NRHS = Dim;
            Real *AB = new Real[4 * N];
            int LDAB = 4;
            int *IPIV = new int[N];
            Real *B = new Real[N * Dim];
            int LDB = N;
            int INFO;

            {
                AB[2] = 4, AB[5] = 2;
                for (int i = 1; i < N - 1; ++i) {
                    AB[i * 4 - 1] = 1;
                    AB[i * 4 + 2] = 4;
                    AB[(i + 1) * 4 + 1] = 1;
                }
                AB[(N - 1) * 4 - 1] = 2;
                AB[(N - 1) * 4 + 2] = 4;
            }

            for (int k = 0; k < Dim; ++k) {
                Real *L = B + k * N;
                L[0] = 6 * cond.c[1][0][k] + 2 * cond.c[1][1][k];
                for (int i = 1; i < N - 1; ++i) L[i] = 6 * cond.c[i + 1][0][k];
                L[N - 1] = 6 * cond.c[N][0][k] - 2 * cond.c[N][1][k];
            }

            gbsv<Real>(&N, &KL, &KU, &NRHS, AB, &LDAB, IPIV, B, &LDB, &INFO);

            ret.N = N;
            ret.p = cond.t[0];
            ret._a.resize(N + 2);
            for (int k = 0; k < Dim; ++k) {
                Real *L = B + k * N;
                ret._a[0][k] = L[1] - 2 * cond.c[1][1][k];
                for (int i = 1; i <= N; ++i) ret._a[i][k] = L[i - 1];
                ret._a[N + 1][k] = L[N - 2] + 2 * cond.c[N][1][k];
            }

            delete[] AB;
            delete[] IPIV;
            delete[] B;

            return ret;
        }
    };

    template<int Dim>
    class Interpolate<Dim, 2, SplineType::cardinalB, BCType::middleP> {
    public:
        static Spline<Dim, 2, SplineType::cardinalB> create(const SplineCondition<Vec<Dim, Real>> &cond) {
            Spline<Dim, 2, SplineType::cardinalB> ret;
            if (cond.N < 2) return ret;

            int N = cond.N;
            ret.N = N;
            ret.p = cond.t[0];

            if (N == 2) {
                ret._a.resize(N + 1);
                for (int k = 0; k < Dim; ++k) {
                    Real &a1 = ret._a[1][k] = 2 * cond.c[1][0][k] - (cond.c[0][0][k] + cond.c[2][0][k]) / 2;
                    ret._a[0][k] = 2 * cond.c[0][0][k] - a1;
                    ret._a[2][k] = 2 * cond.c[2][0][k] - a1;
                }
                return ret;
            }

            int _N = N - 1;
            int KL = 1, KU = 1, NRHS = Dim;
            Real *AB = new Real[4 * _N];
            int LDAB = 4;
            int *IPIV = new int[_N];
            Real *B = new Real[_N * Dim];
            int LDB = _N;
            int INFO;

            {
                AB[2] = 5, AB[5] = 1;
                for (int i = 1; i < N - 2; ++i) {
                    AB[i * 4 - 1] = 1;
                    AB[i * 4 + 2] = 6;
                    AB[(i + 1) * 4 + 1] = 1;
                }
                AB[(N - 2) * 4 - 1] = 1;
                AB[(N - 2) * 4 + 2] = 5;
            }

            for (int k = 0; k < Dim; ++k) {
                Real *L = B + k * _N;
                L[0] = 8 * cond.c[1][0][k] - 2 * cond.c[0][0][k];
                for (int i = 1; i < N - 2; ++i) L[i] = 8 * cond.c[i + 1][0][k];
                L[N - 2] = 8 * cond.c[N - 1][0][k] - 2 * cond.c[N][0][k];
            }

            gbsv<Real>(&_N, &KL, &KU, &NRHS, AB, &LDAB, IPIV, B, &LDB, &INFO);

            ret._a.resize(N + 1);
            for (int k = 0; k < Dim; ++k) {
                Real *L = B + k * _N;
                ret._a[0][k] = 2 * cond.c[0][0][k] - L[0];
                for (int i = 1; i < N; ++i) ret._a[i][k] = L[i - 1];
                ret._a[N][k] = 2 * cond.c[N][0][k] - L[N - 2];
            }

            delete[] AB;
            delete[] IPIV;
            delete[] B;

            return ret;
        }
    };

}


#endif
