#include <iostream>
#include "std.h"
template<typename T>
void tmplParamIsReference(T t) {
  std::cout << "T is reference: " << std::is_reference_v<T> << '\n'
            << &t << '\n';
}
template <class T>
void f(T) {
  cout << "template T \n";
}
template <class T>
void f(T&) {
  cout << "template T& \n";
}

class A{};

// void f(const int&) { cout << "nomarl const int& \n";}

int main()
{
std::cout << std::boolalpha;
int i;
int& r = i;
cout.write(nullptr, 0);
std::cout << &i << '\n';
tmplParamIsReference(i);
tmplParamIsReference(r);
tmplParamIsReference<int&>(i);
tmplParamIsReference<int&>(r);
tmplParamIsReference(1);
A a;
// f(a);
f(std::move(a));
}