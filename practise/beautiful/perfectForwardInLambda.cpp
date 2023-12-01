#include <algorithm>

class BigCost {
  double* ptr;
  const int size = 100;

 public:
  BigCost() { ptr = new double[size]; }
  BigCost(const BigCost& rhs) { ptr = new double[size]; }
  BigCost(BigCost&& rhs) { std::swap(ptr, rhs.ptr); }
  BigCost& operator=(const BigCost&) = delete;
  BigCost& operator=(BigCost&&) = delete;
  // use valgrind show have many BigCost allocated.
  // ~BigCost() { delete[] ptr; }

  void work(){}
};

void getRef(const BigCost&){};
void getRef(BigCost&&){};

int main() {
  // cost 2.
  // BigCost b1;
  // BigCost b2;

  // cost 1.
  // BigCost b1;
  // BigCost b2 = std::move(b1);

  // Lambda capture
  BigCost b1;
  const BigCost cb1;

  // cost 1.
  // auto f = [b1] () {};

  // cost 0.
  // auto f = [&b1] () {};

  // cost 0.
  // auto f = [b1 = std::move(b1)] () {};

  // cost 1.
  // auto f = [](auto&& b) { return [b]() {}; };
  // auto F = f(b1);

  // auto f = [](auto&& b) { return [b = std::move(b)]() {}; };
  // cost 0.
  // auto F = f(b1);
  // cost 1.
  // auto F = f(cb1);

  // forward is useless in capture.
  // auto f = [](auto&& b) { return [b = std::forward<decltype(b)>(b)]() {}; };
  // cost 1.
  // auto F = f(b1);
  // cost 1.
  // auto F = f(cb1);
  // cost 1.
  // auto F = f(BigCost());

  // forward work in parameter.
  // auto f = [](auto&& b) { getRef(std::forward<decltype(b)>(b)); };
  // cost 0.
  // f(b1);
  // cost 0.
  // f(cb1);
  
  // copy inside
  auto f = [](auto& b) {  return [b]() {}; };
  // cost 1.
  // f(b1);
  // cost 1.
  f(cb1);
}