#include <iostream>
#include <type_traits>
#include "std.h"
#include <valarray>

void foo(char*);
class X{};
class K {};
class Y : public X {};
class Z : public K, public Y {};
void foo(int);
int main() {
  char* c = NULL;
  valarray<int> mm(1);
  if (std::is_same<decltype(NULL), decltype(0)>::value)
    std::cout << "NULL == 0" << std::endl;
  if (std::is_same<decltype(NULL), decltype((void*)0)>::value)
    std::cout << "NULL == (void *)0" << std::endl;
  if (std::is_same<decltype(NULL), std::nullptr_t>::value)
    std::cout << "NULL == nullptr" << std::endl;
  foo(0);  // will call foo(int)
  // foo(NULL); // doesn't compile
  foo(nullptr);  // will call foo(char*)
  cout << sizeof(X) << endl;
  cout << sizeof(Y) << endl;
  cout << sizeof(Z) << endl;
  return 0;
}
void foo(char*) {
  std::cout << "foo(char*) is called" << std::endl;
}
void foo(int i) {
  std::cout << "foo(int) is called" << std::endl;
}