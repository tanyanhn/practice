#include <array>
#include <iostream>

constexpr int fibonacci(const int n) {
  return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2);
}

using foo = int (*)(const int);
void functional(foo f) {
  std::cout << f(7) << std::endl;
}
int main() {
  std::array<double, fibonacci(15)> f5arr;
  int f5[fibonacci(5)];
  for (auto i = 0; i < fibonacci(5); ++i) {
    f5[i] = i;
    f5arr[i] = i;
  }
  for (auto i = 0; i < fibonacci(5); ++i) {
    std::cout << f5arr[i] << " ";
  }
  foo f = fibonacci;
  functional(f);
}