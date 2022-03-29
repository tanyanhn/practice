#include <iostream>
#include <thread>

template <class T>
struct A {
  T t;
};

template <class T>
struct A<T*> {
  
};

int main() {
  int a = 0;
  volatile int flag = 0;

  std::thread t1([&]() {
    while (flag != 1)
      ;

    int b = a;
    std::cout << "b = " << b << std::endl;
  });

  std::thread t2([&]() {
    a = 5;
    flag = 1;
  });

  t1.join();
  t2.join();
  return 0;
  A<int> ai;
  A<int*> aip;
}