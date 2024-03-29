#include <iostream>
#include <memory>
using namespace std;

class A;
class B;

class A {
 public:
  std::shared_ptr<B> pointer;
  ~A() { std::cout << "A was destroyed" << std::endl; }
};
class B {
 public:
  std::weak_ptr<A> pointer;
  ~B() { std::cout << "B was destroyed" << std::endl; }
};
int main() {
  std::shared_ptr<A> a = std::make_shared<A>();
  std::shared_ptr<B> b = std::make_shared<B>();
  a->pointer = b;
  b->pointer = a;

  return 0;
}