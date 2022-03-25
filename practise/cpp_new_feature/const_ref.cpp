#include <iostream>
#include <functional>

using namespace std;

std::string returnConstString() {
  return {"in"};
}

template <class T>
void outR(T& t) {
  if constexpr (std::is_rvalue_reference_v<decltype(t)>)
    cout << "is rvalue. \n";
  else if constexpr (std::is_lvalue_reference_v<decltype(t)>)
    cout << "is lvalue. \n";
  else
    cout << "no ref. \n";
  if (std::is_array<T>::value) {
    std::cout << "got array of " << t <<  std::extent<T>::value << " elems\n";
  }
}

template <class T>
void passR(T&& t) {
  if constexpr (std::is_rvalue_reference_v<decltype(t)>)
    cout << "is rvalue. \n";
  else if constexpr (std::is_lvalue_reference_v<decltype(t)>)
    cout << "is lvalue. \n";
  else
    cout << "no ref. \n";
}

void printString(string& s) {
  cout << s << std::endl;
}

template <class T>
void print(T t) {
  // printString(t);
  cout << t;
}


int main() {
  std::string c = "hi";
  outR(c);
  // outR(returnConstString());
  outR("in");
  // outR(std::move(c));
  passR(c);
  passR(std::string("hi"));
  passR(std::move(c));
  auto arr = "his";
  passR(arr);
  passR(returnConstString());
  passR(std::cref(c));
  passR(std::ref(c));
  print(std::ref(arr));
}