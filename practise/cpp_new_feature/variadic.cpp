#include <iostream>

template <class T, class... para, para... l, template<typename> class... templated>
void p(T t, para... pa) {
  std::cout << t << ' ';
  if constexpr (sizeof...(pa) > 0) p(pa...);
  else std::cout << '\n';
}

template <typename... Mixins>
class Point : public Mixins... {
  double x, y, z;

 public:
  Point() : Mixins()...{}
  void visitMixins() {
    this->operator()(static_cast<Mixins&>(*this).help()...);
    (static_cast<Mixins&>(*this).help(),...);
  }
  void operator()(const Mixins&...) {}
};
struct Color {
  char red, green = 'g', blue = 'b';
  const Color& operator()() const{
    p(red, green, blue);
    return *this;
  }
  auto help() { return operator()();}
};
struct Label {
  std::string name = "Label";
  Label& operator()(){
    p(name);
    return *this;
  }
  auto help() { std::cout << "h "; return operator()(); }
};
int main() {
  Point <Label, Color> p;
  p.red = 'r';
  p.visitMixins();
  Point<> p2;
  p2.visitMixins();
}