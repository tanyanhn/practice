#include "std.h"

template <class>
class A {
  public:
  int b;
  static int i;
  A() : b(i++) { cout << "constructor " << b << endl;}
  A(A&& tmp) {b = move(tmp.b); 
  cout << "move constructor " << b << endl;}
  ~A(){ cout << "destructor " << b << endl;}
};

template<> int A<int>::i = 0;


struct Beta_ab {
  Beta_ab() = default;
  Beta_ab(Beta_ab&& tmp) {cout << "Beta_ab && constructor.\n";}
};

struct Beta {
  Beta_ab ab;
  decltype(auto) getAB() const& { return (ab); }
  decltype(auto) getAB() && { return std::move(ab); }
};                        

int main() {
  auto A<int>::*m = &A<int>::b;
  cout << boolalpha;
  cout << " &&.getAB rvalue " << is_rvalue_reference_v<decltype(Beta().getAB())> << endl; 
  const Beta b;
  cout << " &.getAB lvalue "
       << is_lvalue_reference_v<decltype(b.getAB())> << endl;

       auto tmp(Beta().getAB());
}