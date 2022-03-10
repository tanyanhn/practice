#include <iostream>
#include <memory>
#include <cstddef>

struct Storage {
  char a;
  int b;
  double c;
  long long d;
};

struct alignas(std::max_align_t) AlignasStorage {
  long long d;
  char a;
  int b;
  double c;
  long double k;
};

int main() {
  std::cout << alignof(Storage) << std::endl;
  std::cout << alignof(AlignasStorage) << std::endl;
  return 0;
}