#include <iostream>  // std::cout
#include <string>    // std::string
#include <utility>   // std::move
#include <vector>    // std::vector

int main() {
  std::string str = "Hello world.";
  std::vector<std::string> v;

  // use push_back(const T&), copy
  v.push_back(str);
  // "str: Hello world."
  std::cout << "str: " << str << std::endl;

  // use push_back(const T&&), no copy
  // the string will be moved to vector, and therefore std::move can reduce copy
  // cost
  v.push_back(std::move(str));
  // str is empty now
  std::cout << "str: " << str << std::endl;

  return 0;
}