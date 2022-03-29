#include "std.h"

template <typename T1, typename T2, typename T3 = T2>
class C {
 public:
 T1 a1;
 T2 a2;
 T3 a3;
  // constructor for 0, 1, 2, or 3 arguments:
  C(T1 x  , T2 y , T3 z ) : a1(x), a2(y), a3(z) {}
};

int main() {
C c1(22, 44.3, "hi"); 
cout << typeid(decltype(c1)).name() << endl;
}