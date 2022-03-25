#include <cmath>
#include <iostream>

using std::cout;

template <class T>
std::ostream& operator&&(std::ostream& os, T t) {
  return os << t << "\n";
}

template <class... Types>
void print(Types... types) {
  (cout && ... && types);
}

template <class T, class... Types>
void p(T t, Types... types) {
  cout << t << "\n";
  if constexpr (sizeof...(Types))  // also types
    p(types...);
}

int main() {
  int i = 1, ii = -9;
  double d = M_PI, dd = -M_Ef64;
  auto s = "hello", ss = "world!";
  print(ss, d, ii, s, i, "my", 'a', dd, '\n');
  p(ss, d, ii, s, i, "my", 'a', dd);
}