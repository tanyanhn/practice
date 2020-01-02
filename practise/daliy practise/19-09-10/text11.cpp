#include "Point11.h"
using namespace std;

int main(int argc, char *argv[])
{
    Point<2> a(1, 2);
    const double *A = a.read();
    cout << A[0] << ", " << A[1] << "\n";
    Point<3> b(1, 2, 3);
    A = b.read();
    cout << A[0] << ", " << A[1] << "\n";
    // Convenient!
    cout << a[0] << ", " << A[1] << "\n";
    Point<3> c(b);
    c = b;
    cout << "b + c = " << b + c << "\n";
    // Error, dimension not match.
    // cout << " a + b = " << a + b << "\n";
    return 0;
}
