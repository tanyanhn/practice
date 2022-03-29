#include "std.h"

template <class T>
struct Outer {
  template <class U>
  struct Inner {
    static U u;
  };
};

template <>
struct Outer<void> {
  template <class U>
  struct Inner {
    static U u;
  };
};

template <class U>
U Outer<void>::Inner<U>::u{};

template <class T>
template <class U>
U Outer<T>::Inner<U>::u;

template <>
struct Outer<void>::Inner<char> {
    static char u;
};

char Outer<void>::Inner<char>::u = 'c';

int main() {
  cout << Outer<void>::Inner<int>::u << endl;
  cout << Outer<int>::Inner<double>::u << endl;
  cout << Outer<void>::Inner<char>::u << endl;
}