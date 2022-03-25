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
int null = 0;
int main()
{
RefMem<int> rm1, rm2;
rm1 = rm2;
// RefMem<int&> rm3;
// RefMem<int&, 0> rm4;
// extern int null;
RefMem<int&,null> rm5, rm6;
// rm5 = rm6;
}