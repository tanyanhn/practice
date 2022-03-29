template<typename T, T Z = T{}>
class RefMem {
 private:
  template <class U>
  static inline U u;
T zero;
public:
RefMem() : zero{Z} {
}
};
template <class T, T t>
class RefMem<T*, t>;
// class X{};
template <class X* x>
struct Y {
};
extern X x;
int null = 0;
int main() {
  // RefMem<double*, nullptr> r;
  Y<&x> y;
RefMem<int> rm1, rm2;
rm1 = rm2;
// RefMem<int&> rm3;
// RefMem<int&, 0> rm4;
// extern int null;
RefMem<int&,null> rm5, rm6;
// rm5 = rm6;
}