#include "std.h"

template <typename F,
          typename... Args,
          typename = decltype(std::declval<F>()(std::declval<Args&&>()...))>
std::true_type isValidImpl(void*);
// fallback if helper SFINAE.d out:
template <typename F, typename... Args>
std::false_type isValidImpl(...);
// define a lambda that takes a lambda f and returns whether calling f with args
// is valid
inline constexpr auto isValid = [](auto f) {
  return [](auto&&... args) {
    return decltype(isValidImpl<decltype(f), decltype(args)&&...>(nullptr)){};
  };
};
// helper template to represent a type as a value
template <typename T>
struct TypeT {
  using Type = T;
};
// helper to wrap a type as a value
template <typename T>
constexpr auto type = TypeT<T>{};
// helper to unwrap a wrapped type in unevaluated contexts
template <typename T>
T valueT(TypeT<T>);  // no definition needed

class X {
  void f() &&;
  public:
  X(int&);
  int first;
  void f() &;
};

int main() {
   auto isDefaultConstructible =
      isValid([](auto x) -> decltype(decltype(valueT(x))()) {});
  cout << boolalpha;
  cout << "type<int> :" << isDefaultConstructible(type<int>) << endl;
  cout << "type<int&> :" << isDefaultConstructible(type<int&>) << endl;

  auto haveMember = isValid([](auto x) -> decltype(valueT(x).first) {});
  cout << "type<X> have first :" << haveMember(type<X>) << endl;

  auto haveMemberF =
      isValid([](auto x) -> decltype(valueT(x).f()) {});
  cout << "type<X> have f() :" << haveMember(type<X>) << endl;

  auto intConstructor = 
    isValid([](auto x, auto i) -> decltype(decltype(valueT(x))(valueT(i))) {});
  cout << "type<X> have X(int) :" << intConstructor(type<X>, type<const int>) << endl;
}