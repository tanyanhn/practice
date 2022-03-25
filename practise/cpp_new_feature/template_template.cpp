#include <vector>
#include <iostream>
#include <deque>

using std::cout;
using std::vector;

template <typename T, template <typename> class Containor, typename std::enable_if_t<true>* b = nullptr>
class Stack {
  Containor<T> vec;

 public:
  Stack(std::initializer_list<T> i) : vec(i) {}
  void print() {
    for (auto i : vec) {
      cout << i << "\n";
   }
  }
};

// pass in g++, however fail in clang.
int main() {
  Stack<double, std::deque> s{9.3, -1.23, 0.34};
  s.print();
}