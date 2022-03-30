#include <typeinfo>
#include <iostream>
#include <type_traits>
#include "std.h"
class Base {
  virtual void f() = 0;
};
struct Decider : public Base {
  // #if defined(DYNAMIC)
   void f() override{}
  virtual ~Decider() {
    std::cout << "Decider destructor.";
}
// #endif
};
Decider d;

struct X {
  int i;
  X() = default;
  constexpr X(int m) : i(m) {};
  X operator+(const X& x) const ;
};

template<class T1, class T2>
struct PlusResult {
  using type = decltype(declval<T1>() + declval<T2>());
};

template<class T1, class T2>
using Prt = typename PlusResult<T1, T2>::type;

template<class T>
class isDefaultConstructor {
  template<class U, U = U(integral_constant<int64_t, 1000000>::value)>
  static int test(void*);
  template<class>
  static float test(...);
  public:
  constexpr static auto value = is_same_v<int, decltype(test<T>(nullptr))>;
};

template <class T>
class isDefaultConstructor2 {
  template <class U, class  = decltype(declval<U>() + declval<U>())>
  static int test(void*);
  template <class>
  static float test(...);

 public:
  constexpr static auto value = is_same_v<int, decltype(test<T>(nullptr))>;
};

int main() {
  char const* name = typeid(d).name();
  while(*name++ != '\0')
    std::cout << *name;
  std::cout << "\n" <<  sizeof(d) << '\n';
  Prt<X, X> p;
  cout << boolalpha;
  cout << "X(i)  exist " << isDefaultConstructor<X>::value << endl;
  cout << "X + X  exist " << isDefaultConstructor2<X>::value << endl;
}