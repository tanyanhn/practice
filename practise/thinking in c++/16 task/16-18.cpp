#include <iostream>
#include <sstream>
#include <cassert>
#include <cstring>
#include <cstddef>
using namespace std;

template<class T, size_t N>
class Array {
    T i[N];
public:
    Array() { memset(i, 0, N * sizeof(*i)); }
    T& operator[] (int x) {
        assert(x >= 0 && x < N);
        return i[x];
    }
    // Inline member template definitions
    // (Tends to work with most compliers):
    friend ostream& operator<<(ostream& os, const Array<T, N>& ia) {
        for (int j = 0; j < N; j++){
            os << ia.i[j];
            if(j != N - 1)
                os << ", ";
        }
    }
    friend istream& operator>>(istream& is ,Array<T, N>& ia) {
        for(int j = 0; j < N; j++)
            is >> ia.i[j];
        return is;
    }

    // Declarations for out-of line definitions
    // (Which don't work with many compilers):
};

    int main() {
    stringstream input("47 34 56 92 103");
    Array<int, 5> I;
    input >> I;
    I[4] = -1; // Use overloaded operator
    cout << I;
}
