// Non-inline template definition
#include "../require.h"

template<class T>
class Array {
    static const int size = 100;
    T A[size];
public:
    T& operator[](int index);
};

template<class T>
T& Array<T>::operator[](int index) {
    require(index >= 0 && index < size, "Index out of range");
    return A[index];
}

int main() {
Array<float> fa;
fa[0] = 1.414;
}
