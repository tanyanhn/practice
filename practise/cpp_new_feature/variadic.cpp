#include <iostream>

template <class T, class... para>
void p(T t, para... pa) {
  std::cout << t << ' ';
  if constexpr (sizeof...(pa) > 0) p(pa...);
}

template <typename... Mixins>
class Point : public Mixins... {
  double x, y, z;

 public:
  Point() : Mixins()...{}
  void visitMixins() {
    this->operator()(static_cast<Mixins&>(*this)()...);
  }
  void operator()(const Mixins&...) {}
};
struct Color {
  char red, green = 'g', blue = 'b';
  const Color& operator()() const{
    p(red, green, blue);
    return *this;
  }
};
struct Label {
  std::string name = "Label";
  Label& operator()(){
    p(name);
    return *this;
  }
};
int main() {
  Point<Color, Label> p;
  p.red = 'r';
  p.visitMixins();
}