#include <iostream>

template <typename T>
int test(typename T::X const*){
  return 1;
}
// template <typename T>
// int test(...){
//   return 2;
// }

class A {
  public:
  using X=double;
};

int main() {
  // auto* f = &test<int>;
  auto* g = &test<A>;
  const A::X dp = 0.0;
  std::cout  << "\n" << g(&dp) << '\n';
}