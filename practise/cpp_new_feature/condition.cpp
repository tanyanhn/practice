#include "std.h"

template <class T>
struct MakeUnsigned {
//   static_assert(!is_same_v<T, bool>, "bool");
  using Type = typename make_unsigned<T>::type;
};

template <class T>
struct Wrapper {
  using Type = void*;
};

template <class T>
struct SafeSinged {
  using Type = typename conditional<is_integral_v<T> && !is_same_v<T, bool>,
                                    MakeUnsigned<T>,
                                    Wrapper<T>>::type::Type;
};

template <class T>
void printName(T t) {
  const auto *p = typeid(t).name();
  while (*p != '\0')
    cout << *p++;
  cout << endl;
}

int main() {
  SafeSinged<double>::Type t1;
    printName(t1);
  SafeSinged<long>::Type t2;
  printName(t2);
  SafeSinged<bool>::Type t3;
  printName(t3);
  double arrd[10];
  auto& ref = arrd;
  cout << sizeof(ref) << endl;
  input_iterator_tag t;
}