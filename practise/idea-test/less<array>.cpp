#include <array>
#include <vector>
#include "../../catch.hpp"

using namespace std;

TEST_CASE(){
  array<int, 3> arr2{1, 3, 2};
  array<int, 3> arr1{1, 2, 3};
  array<int, 4> arr3{1, 2, 3, 4};
  REQUIRE(arr1 < arr2);

  less<array<int, 3>> op;
  REQUIRE(op(arr1, arr2));

  
  vector<int> v2{1, 3, 2};
  vector<int> v1{1, 2, 3};
  vector<int> v3{1, 2, 3, 4};
  REQUIRE(v1 < v2);

  less<> opv;
  REQUIRE(opv(v1, v2));
  REQUIRE_FALSE(opv(v3, v1));

}