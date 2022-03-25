#include <variant>
#include <tuple>
#include <iostream>

template <size_t n, typename... T>
constexpr auto tuple_index(const std::tuple<T...>& tpl,
                                          size_t i) -> std::variant<T...> {
  if constexpr (n >= sizeof...(T)) {
    throw std::out_of_range("越界.");
}
  if (i == n) {
    return std::variant<T...>{std::in_place_index<n>, std::get<n>(tpl)};
}
  return tuple_index<(n < sizeof...(T) - 1 ? n + 1 : 0)>(tpl, i);
}
template <typename... T>
constexpr auto tuple_index(const std::tuple<T...>& tpl,
                                         size_t i) {
  return tuple_index<0>(tpl, i);
}
template <typename T0, typename... Ts>
auto operator<<(std::ostream& s, std::variant<T0, Ts...> const& v) -> std::ostream& {
  std::visit([&](auto&& x) { s << x; }, v);
  return s;
}

auto main() -> int {
  auto t = std::make_tuple(3.1, "hello,", 'a');
  int i = 2;
  std::cout << tuple_index(t, i);
}