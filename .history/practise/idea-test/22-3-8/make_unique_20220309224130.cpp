#include <memory>
#include <iostream>
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class A {
  int a;
  double b;
  public:
  A(int aa, double bb) : a(aa), b(bb) {}
  void print() const {
    std::cout << a << b << "\n";
  }
};

auto main() -> int {
  auto p = make_unique<A>(-1, 34.1);
  p->print();
}