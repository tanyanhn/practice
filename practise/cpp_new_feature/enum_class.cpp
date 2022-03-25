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

int main() {
  cout << Per << "\n";
  cout << (int)aC::Per << "\n";
  cout << (char)cC::Per << "\n";
}