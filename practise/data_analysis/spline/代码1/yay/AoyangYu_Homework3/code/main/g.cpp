#include "../lib/SplineBuilder.hpp"
#include <fstream>
#include <string>
#include <valarray>
#include <cmath>

using namespace std;

void _G(int n, ostream &os) {
    using va = valarray<Real>;

    Real L = -1.7, R = n + 0.1, step = 0.01;
    int T = (R - L) / step;
    va X(T + 1);
    for (int i = 0; i <= T; ++i) {
        Real x = L + i * step;
        X[i] = x;
    }

    va a[n + 2][n + 2];
    for (int i = 0; i <= n + 1; ++i) {
        auto f = [i, n](Real x) -> Real { return x < i - 1 ? pow(i - 1 - x, n) : 0; };
        va &b = a[i][0];
        b.resize(T + 1);
        transform(begin(X), end(X), begin(b), f);
    }

    for (int j = 1; j <= n + 1; ++j) {
        for (int i = j; i <= n + 1; ++i) {
            a[i][j] = (a[i][j - 1] - a[i - 1][j - 1]) / j;
            if (i == n + 1 && j == n + 1) a[i][j] *= n + 1;
        }
    }

    os << n << endl;
    for (int i = 0; i <= T; ++i) {
        os << X[i] << endl;
    }
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= i; ++j) {
            os << "---" << endl;
            os << i << ' ' << j << endl;
            for (int k = 0; k <= T; ++k) {
                os << a[i][j][k] << endl;
            }
        }
    }

}

void G() {
    cout << "--- G ---" << endl;
    cout << "see the programming report" << endl;
    int Ns[] = {1, 2, 3};
    for (int n: Ns) {
        string oname = "./outs/G_";
        oname += to_string(n) + ".out";
        ofstream os(oname);
        _G(n, os);
    }
}