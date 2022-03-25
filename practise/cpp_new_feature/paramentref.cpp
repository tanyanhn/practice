#include <iostream>
template<typename T>
void tmplParamIsReference(T t) {
  std::cout << "T is reference: " << std::is_reference_v<T> << '\n'
            << &t << '\n';
}
int main()
{
std::cout << std::boolalpha;
int i;
int& r = i;
std::cout << &i << '\n';
tmplParamIsReference(i);
tmplParamIsReference(r);
tmplParamIsReference<int&>(i);
tmplParamIsReference<int&>(r);
tmplParamIsReference(1);
}