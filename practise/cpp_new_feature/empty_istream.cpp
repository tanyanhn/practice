#include "std.h"

int main() {
  ifstream is("istream.txt");
  double a = 0, b = 0;
  is >> a >> b >> b;
  cout << a << endl;
  cout << b << endl;
}