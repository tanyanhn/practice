#include <vector>

using namespace std;

int main() {
  vector<double> v;
  for(int i = 0; i != 1000; ++i) {
    v.push_back(i^(i *7));
  }

  vector<double> vc;
  for(auto a : v) {
    for(auto b : v) {
      vc.push_back(a * b);
    }
  }
}