#include "Point.h"

int main(int argc, char *argv[])
{
    Point a(1, 2);
    Point b(3, 4);
    // Convenient!
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "a + b = " << a + b << "\n";
    // Error! Formula a+=b will return a lvalue, however,
    // current << only accept const .
    // std::cout << "a += b is " << a+= b << "\n";
    a += b;
    std::cout << "a += b is " << a << "\n";
}
