class MyInt {
public:
  int v;
  MyInt(int i) : v(i) {}
  operator int() {return v;} 
};
MyInt operator - (MyInt const& v){ return {-v.v};}
bool operator > (MyInt const& l, MyInt const& r){ return l.v > r.v;  }
bool operator > (MyInt const& l, int r){ return l.v > r;  }
using Int = MyInt;
template<typename T>
void f(T i)
{
if (i>0) {
g(-i);
}
}
void g(Int i);
int main() {
  g(42);
}

extern template void f(Int);
extern template void f(int);

template void f<Int>(Int);

template<typename T>
void f1(T x)
{
g1(x); // #1
}
void g1(int)
{
}

// #1
void g(Int i)
{
// #2
f<Int>(i);  // point of call
            //  f(42);
// #3
f1<Int>(7);
// f1<int>(7);// ERROR: g1 not found!
}
// #4

