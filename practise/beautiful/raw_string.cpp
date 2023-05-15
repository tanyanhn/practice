#include <iostream>
#include <string>
#include <type_traits>

void foo();

int main() {
  std::string str = R"(C:\Path\To\File)";
  std::cout << str << std::endl;
  if  (1) {

  } else {
    foo();
  }
  return 0;
}