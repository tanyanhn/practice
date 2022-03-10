#include <atomic>
#include <iostream>
#include <vector>
#include <array>
#include <thread>

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

class C {
  int a;
  virtual void f();
};

int main() {
  std::atomic<A> a;
  std::cout << std::boolalpha << a.is_lock_free() << std::endl;
  std::atomic<B> b;
  std::cout << std::boolalpha << b.is_lock_free() << std::endl;
  std::atomic<int (*)()> c;
  std::cout << std::boolalpha << c.is_lock_free() << std::endl;
  // std::atomic<std::vector<int>> cd;
  // std::cout << std::boolalpha << cd.is_lock_free() << std::endl;
  std::atomic<std::array<int, 1>> d;
  std::cout << std::boolalpha << d.is_lock_free() << std::endl;
  std::atomic<std::array<int, 2>> e;
  std::cout << std::boolalpha << e.is_lock_free() << std::endl;
  std::atomic<std::array<int, 3>> cf;
  std::cout << std::boolalpha << cf.is_lock_free() << std::endl;
  std::atomic<std::array<long, 1>> f;
  std::cout << std::boolalpha << f.is_lock_free() << std::endl;
  std::atomic<std::array<u_int64_t, 2>> g;
  std::cout << std::boolalpha << g.is_lock_free() << std::endl;
  std::atomic<std::array<char, 4>> h;
  std::cout << std::boolalpha << h.is_lock_free() << std::endl;
  std::atomic<std::array<char, 5>> l;
  std::cout << std::boolalpha << l.is_lock_free() << std::endl;
  std::atomic<std::array<bool, 4>> m;
  std::cout << std::boolalpha << m.is_lock_free() << std::endl;
  std::atomic<std::array<bool, 5>> n;
  std::cout << std::boolalpha << n.is_lock_free() << std::endl;
  // std::atomic<C> o;
  // std::cout << std::boolalpha << o.is_lock_free() << std::endl;

  std::atomic<int*> ptr(nullptr);
  int v;
  std::thread consumer([&]() {
    int* p;
    while (!(p = ptr.load(std::memory_order_relaxed)))
      ;

    std::cout << "p: " << *p << std::endl;
    std::cout << "v: " << v << std::endl;
  });
  std::thread producer([&]() {
    int* p = new int(42);
    v = 1024;
    ptr.store(p, std::memory_order_release);
  });
  producer.join();
  consumer.join();
  return 0;
}