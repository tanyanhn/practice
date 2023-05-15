#include "../idea-test/emGridtest/Tensor.h"
#include "std.h"

struct X {
  vector<double> vd[2];
  double d = 0;
  int* p = nullptr;
};

template <class T, class U = T>
T* tensorGet(T* t) {
  return t;
}

template <class U>
U* tensorGet(nullptr_t) {
  return new U;
}

int main() {
  int N = 32;
  Box<2> bx(0, N -1);
  Tensor<X*, 2>* ptr = new Tensor<X*, 2>(bx);
  auto& te = *ptr;
  if (te(0, 0) == nullptr)
    cout << "nullptr" << endl;

  if (tensorGet<X>(te(0, 0)) == nullptr)
    cout << "nullptr" << endl;
  else
    cout << "initializer" << endl;
}