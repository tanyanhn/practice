#include "std.h"

// primary template:
template <typename T, typename = std::void_t<>>
struct IsNothrowMoveConstructibleT : std::false_type {
  static const char value = 'm';
};template<typename T, typename = std::void_t<>>
struct IsNothrowAssignConstructibleT : std::false_type
{
  static const char value = 'a';
};
// partial specialization (may be SFINAE'd away):
template <typename T>
struct IsNothrowMoveConstructibleT<T,
                                   std::void_t<decltype(remove_reference_t<T>(std::declval<T>()))>>
    : std::bool_constant<noexcept(remove_reference_t<T>(std::declval<T>()))> {};

template <typename T>
struct IsNothrowAssignConstructibleT<T,
                                   std::void_t<decltype(remove_reference_t<T>(std::declval<T&>()))>>
    : std::bool_constant<noexcept(remove_reference_t<T>(std::declval<T&>()))> {};

class X {
  public:
//    X() = default;
   X(const X&){};
   private:
   X(X&&)  {};
};

int main() {
  cout << boolalpha;
  cout << IsNothrowMoveConstructibleT<X>::value << endl;
  cout << IsNothrowAssignConstructibleT<X>::value << endl;
}