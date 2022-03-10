#include <memory>
#include <iostream>
template <typename T, typename... Args>
auto make_unique(Args&&... args) -> std::unique_ptr<T> {
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

struct Foo {
  Foo() { std::cout << "Foo::Foo" << std::endl; }
  ~Foo() { std::cout << "Foo::~Foo" << std::endl; }
  void foo() { std::cout << "Foo::foo" << std::endl; }
};

void f(const Foo&) {
  std::cout << "f(const Foo&)" << std::endl;
}

int main() {
  auto p = make_unique<A>(-1, 34.1);
  p->print();
  std::unique_ptr<Foo> p1(std::make_unique<Foo>());

  // p1 is not empty, prints
  if (p1)
    p1->foo();
  {
    std::unique_ptr<Foo> p2(std::move(p1));

    // p2 is not empty, prints
    f(*p2);

    // p2 is not empty, prints
    if (p2)
      p2->foo();

    // p1 is empty, no prints
    if (p1)
      p1->foo();

    p1 = std::move(p2);

    // p2 is empty, no prints
    if (p2)
      p2->foo();
    std::cout << "p2 was destroyed" << std::endl;
  }
  // p1 is not empty, prints
  if (p1)
    p1->foo();

  // Foo instance will be destroyed when leaving the scope
}