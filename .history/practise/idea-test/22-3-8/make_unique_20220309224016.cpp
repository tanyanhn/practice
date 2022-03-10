#include <memory>

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class A {
  int a;
  double b;
  public:
  A(int aa, double bb) : a(aa), b(bb) {}
};

auto main() -> int {

}