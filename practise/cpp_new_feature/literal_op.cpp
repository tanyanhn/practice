#include "std.h"

template <char... cs>
int operator"" _B7() {
  std::array<char, sizeof...(cs)> chars{cs...};
  for (char c : chars) {
     std::cout << "'" << c << "'";
  }
  std::cout << '\n';
  return 0;
}

template <typename T>
class Array {
 public:
  using iterator = T*;
};
template <typename T>
void f(typename Array<T>::iterator first, typename Array<T>::iterator last);
template <typename T>
void f(T, T);

template <typename T>
T& beginb(T& array) {
  cout << 'T' << endl;
  return array;
}
template <typename Container>
// decltype(auto) 
typename Container::iterator beginb(Container& c) {
  cout << "containor" << endl;
  return c.begin();
  // return 0;
}

int main() {
  auto i = 152.694_B7;
  cout << i << endl;
  auto d = 0715_B7;
  auto s = 0;
  // f<int&>(d, s);
  int c[20];
  beginb(c);
}