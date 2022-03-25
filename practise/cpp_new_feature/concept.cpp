#include <concepts>
#include <iostream>
#include <list>
#include <map>
#include <vector>
using namespace std;

template <class T>
concept Compareable = std::totally_ordered<T>;

template <class V>
  requires std::totally_ordered<V>
struct A {
 public:
  using Vertex = V;
  Vertex x;
  A operator()() { return *this; }
};

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
  bool operator<(const C& rhs) const { return true; }
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
}