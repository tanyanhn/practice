#include <iostream>

class B{}
template <class T>
class A {
  T* a;
  class B* b;
  // class T* t;
  friend class B;
  // friend class T;
};

int main(){
  A<std::pair<int, int>> a;
}