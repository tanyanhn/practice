#include "std.h"

template<typename C>
struct A {
  bool operator()(int i, int j) const {
    return C::template f<2>(i, j);
  }
};

struct B {
  template<int I>
  static bool f(int i, int j);
};

template <int I>
bool B::f(int i, int j) {
  return (i - I ) < j;
}

int main() {
  int i = 0;
  int j = -1;
  A<B> a;
  cout << boolalpha;
  cout << a(i, j) << endl;;
}