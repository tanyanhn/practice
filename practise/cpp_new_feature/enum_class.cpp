#include <iostream>
using namespace std;


enum bC {
  Per,
  Num
};

enum class aC {
  Per = -1,
  Gor,
};

enum class cC : char {
  Per = 9,
};

class X {
  public:
  int i;
};
struct Y : X {};
class Z : X {};

int main() {
  cout << Per << "\n";
  cout << (int)aC::Per << "\n";
  cout << (char)cC::Per << "\n";
  Y y;
  cout << y.i << endl;
  Z z;
  // cout << z.i << endl;
}