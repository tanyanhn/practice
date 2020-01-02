#include <iostream>

#include "../require.h"
using namespace std;

class A {
    double i;
public:
    A(double ii = 1) : i(ii) {}
     operator const double() const {
         return i;
     }
    ~A(){}
    /* const A operator+(const A& b) const {
        return A( i + b.i);
    }
    const A operator-(const A& b) const {
        return A( i - b.i);
        }*/
    A& operator++() {
        i++;
        return *this;
    }
    A& operator--() {
        i--;
        return *this;
    }
    const A operator++(int) {
        A a(i);
        i++;
        return a;
    }
    const A operator--(int) {
        A a(i);
        i--;
        return a;
    }
    /*void print(ostream& os = cout) const {
        os << "i = " << i << "\n";
        }
    friend ostream& operator<<(ostream& os, const A& a){
        a.print();
        }*/
    friend const A operator+(const A& a, const A& b) {
        return A(a.i + b.i);
    }
    friend const A operator-(const A& a, const A& b) {
        return A(a.i - b.i);
    }
    A& operator-() {
        i = -i;
        return *this;
    }
    friend const A operator*(const A& a, const A& b) {
        return A(a.i * b.i);
    }
    friend const A operator/(const A& a, const A& b) {
        
        return A(a.i / b.i);
    }
    A& operator=(const A& b) {
        i = b.i;
        return *this;
    }
};

int main(int argc, char *argv[])
{
    A a, b(3), c(9);
    a = a + b;
    cout << a << endl;
    /*(-a).print();
    (a + b - c).print(cout);
    (++a).print(cout);
    (a++).print();
    (--a).print();
    (a--).print();
    cout << a ;*/
    a = (b * a  - a / c);
    cout << --a << endl;
    return 0;
}
