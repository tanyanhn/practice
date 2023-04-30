#include <cstdlib>
#include "../../catch.hpp"
#include "YtanFunction.h"

using std::vector;

TEST_CASE("Partition", "[yTan]") {
  auto size = 1000;
  vector<vector<int>> connected(size);
  for (auto& v : connected) {
    v.resize(size, 0);
  }

  for (int k = 0; k < size * 2; ++k) {
    auto i = random() % size;
    auto j = random() % size;
    connected[i][j] = 1;
    connected[j][i] = 1;
  }

  auto res = yTanPartition(connected);

  size_t s = 0;
  for (int a = 0; a < res.size(); ++a) {
    s += res[a].size();
    for (int b = a + 1; b < res.size(); ++b) {
      for (auto i : res[a]) {
        for (auto j : res[b]) {
          REQUIRE((connected[i][j] == 0 && i != j));
        }
      }
    }
  }
  REQUIRE(s == size);
}