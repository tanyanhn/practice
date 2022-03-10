#include <atomic>
#include <iostream>
#include <vector>
#include <array>

struct A {
  float x;
  int y;
  // long long z;
  // size_t m;
  // unsigned int k;
  // double d;
  // int* p;
  // int l;
};

class B {
  A a;
  int s;
};

int main() {
  std::atomic<A> a;
  std::cout << std::boolalpha << a.is_lock_free() << std::endl;
  std::atomic<B> b;
  std::cout << std::boolalpha << b.is_lock_free() << std::endl;
  std::atomic<int (*)()> c;
  std::cout << std::boolalpha << c.is_lock_free() << std::endl;
  // std::atomic<std::vector<int>> d;
  // std::cout << std::boolalpha << d.is_lock_free() << std::endl;
  std::atomic<std::array<int,1 >> d;
  std::cout << std::boolalpha << d.is_lock_free() << std::endl;
  return 0;
}