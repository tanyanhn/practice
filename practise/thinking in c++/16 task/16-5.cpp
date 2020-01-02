#include <iostream>
#include <cassert>
#include <cstddef>// For size_t
using namespace std;

template<class T>
T Fib(const T& n) {
    const size_t sz = 100;
    static T f[sz]; // Intialized to zero

    static size_t nFilled = 2;
    f[0] = f[1] = 1; // T must be convertible from int
    size_t int_n = size_t(n);
    assert(n < sz);

    while (int_n >= nFilled) {
        cout << "growing to " << n << " (sizeof(T)) == " << sizeof(T) << ")\n";
        f[nFilled] = f[nFilled - 1] + f[nFilled - 2];
        nFilled++;
    }
    return f[int_n];
}

int main() {
    for(double x = 8.0; x >= 0.0; --x)
        cout << "Fib(" << x << ") == " << Fib(x) << endl;
}
