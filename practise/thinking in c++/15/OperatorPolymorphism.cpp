// Polymorphism with overloaded operators
#include <iostream>
using namespace std;

class Matrix;
class Scalar;
class Vector;

class Math {
public:
    virtual Math& operator*(Math& rv) = 0;
    virtual Math& multiply(Matrix*) = 0;
    virtual Math& multiply(Scalar*) = 0;
    virtual Math& multiply(Vector*) = 0;
    virtual ~Math() {}
};

class Matrix : public Math {
public:
    Math& operator*(Math& rv) {
        return rv.multiply(this); // 2nd dispacth
    }
    Math& multiply(Matrix*) {
        cout << "Matrix * Matrix\n";
        return *this;
    }
    Math& multiply(Scalar*) {
        cout << "Scalar * Matrix\n";
        return *this;
    }
    Math& multiply(Vector*) {
        cout << "Vector * Matrix\n";
        return *this;
    }
};

class Scalar : public Math {
public:
    Math& operator*(Math& rv) {
        return rv.multiply(this); // 2nd dispacth
    }
    Math& multiply(Matrix*) {
        cout << "Matrix * Scalar\n";
        return *this;
    }
    Math& multiply(Scalar*) {
        cout << "Scalar * Scalar\n";
        return *this;
    }
    Math& multiply(Vector*) {
        cout << "Vector * Scalar\n";
        return *this;
    }
};

class Vector : public Math {
public:
    Math& operator*(Math& rv) {
        return rv.multiply(this); // 2nd dispacth
    }
    Math& multiply(Matrix*) {
        cout << "Matrix * Vector\n";
        return *this;
    }
    Math& multiply(Scalar*) {
        cout << "Scalar * Vector\n";
        return *this;
    }
    Math& multiply(Vector*) {
        cout << "Vector * Vector\n";
        return *this;
    }
};

int main() {
    Matrix m; Vector v; Scalar s;
    Math* math[] = { &m, &v, &s};
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++){
            Math& m1 = *math[i];
            Math& m2 = *math[j];
            m1 * m2;
        }
}
