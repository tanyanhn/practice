#include <vector>
#include <set>

template <class T>
using vector = std::vector<T>;

template <class T>
using set = std::set<T>;

int main() {
  vector<double> v{0, 3, 9.0};
  std::set<double> s{{9, 3.3, -1}};
}