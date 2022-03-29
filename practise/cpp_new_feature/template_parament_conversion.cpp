template<typename T, T nontypeParam>class C;
struct Base {
int i;
} base;
struct Derived : public Base {};
Derived derived{};
C<Base*, static_cast<Base*>(&derived)>* err1; 
int a[10];
C<int*, &a[0]>* err3;

int main() {
  err3 = nullptr;
}