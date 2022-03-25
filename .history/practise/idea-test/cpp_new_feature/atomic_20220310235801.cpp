#include <atomic>
#include <iostream>

struct A {
  float x;
  int y;
  // long long z;
  // size_t m;
  // unsigned int k;
};

class B {
  A a;
};

int main() {
  std::atomic<A> a;
  std::cout << std::boolalpha << a.is_lock_free() << std::endl;
  std::atomic<B> b;
  std::cout << std::boolalpha << b.is_lock_free() << std::endl;
  return 0;
}