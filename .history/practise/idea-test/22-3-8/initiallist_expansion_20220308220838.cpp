#include <initializer_list>
#include <iostream>

template <typename T, typename... Ts>
auto printf3(T value, Ts... args) {
  std::cout << value << std::endl;
  (void)std::initializer_list<T>{
      ([&args] { std::cout << args << std::endl; }(), value)...};
}

int main() {
  printf3(1, " name", 3.1, 'a');
}