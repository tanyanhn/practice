#include <typeinfo>
#include <iostream>
#include <type_traits>
class Base {
  virtual void f();
};
class Decider : public Base {
  // #if defined(DYNAMIC)
  virtual void f(){}
  virtual ~Decider() {
    std::cout << "Decider destructor.";
}
// #endif
};
extern Decider d;
int main() {
  char const* name = typeid(d).name();
  while(*name++ != '\0')
  std::cout << *name;
  std::cout << "\n" <<  sizeof(d);
return (int)sizeof(d);
}