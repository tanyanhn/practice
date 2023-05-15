#include "std.h"

int main() {
  string s;
  cout << boolalpha;
  cout << "max_size: " << s.max_size() << endl;
  cout << is_same_v<decltype(s.max_size()), uint64_t> << endl;
  cout << sizeof(decltype(s.max_size())) << endl;
  tuple<int, double> t;
}