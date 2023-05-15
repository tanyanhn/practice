#include <concepts>
#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

namespace detail {
 
template<class T>
auto test_returnable(int) -> decltype(
    void(static_cast<T(*)()>(nullptr)), std::true_type{}
);
template<class>
auto test_returnable(...) -> std::false_type;
 
template<class From, class To>
auto test_implicitly_convertible(int) -> decltype(
    void(std::declval<void(&)(To)>()(std::declval<From>())), std::true_type{} // like g(), f() test move constructor
);
template<class, class>
auto test_implicitly_convertible(...) -> std::false_type;
 
} // namespace detail

template <class T>
concept Compareable = std::totally_ordered<T>;

template <class T, class U>
concept ass = requires(T lhs, U&& rhs) {
                { lhs = std::forward<U>(rhs) } -> same_as<T>;
              };

class X {
  public:
   X(){ cout << "X()\n";}
   X(const X&) {
     cout << "X(const X&)\n";
   }
  //  X(X&&) = delete;
   X& operator=(const X&) = default;
   ~X() = default;
};

void f(X){}
X g(){ X x; return x;}

template <class T, class U = T>
requires ass<T, U>
// requires  (     decltype(detail::test_implicitly_convertible<T, T>(0))::value)
struct M {
  std::remove_reference_t<T> t;
};

template <class V>
  requires std::totally_ordered<V>
struct A {
 public:
  using Vertex = V;
  Vertex x;
  A operator()() { return *this; }
};

std::true_type t;

template <class T>
struct B {
  using cA = A<T>;
  using Vertex = typename cA::Vertex;
  cA a;
  B operator()() { return *this; }
  template <class U>
  B print(U i) {
    cout << i << endl;
    return *this;
  }
};

class C {
  int c;

 public:
  char operator<(const C& rhs) const { return true; }
  bool operator<=(const C& rhs) const { return c <= rhs.c; }
  bool operator>(const C& rhs) const { return true; }
  bool operator>=(const C& rhs) const { return c >= rhs.c; }
  bool operator==(const C& rhs) const { return c == rhs.c; }
  // bool operator!=(const C& rhs) const { return c != rhs.c; }
};

int main() {
  // B<map<int, int>::iterator> l;
  // B<vector<int>::iterator> l;
  B<C> p;
  p();
  int i;
  p.print<double>(i);
  B<std::pair<int, bool>> b;
  cout << b.a.x.second << endl;
  M<X&, X> m;
  // f(g());
}