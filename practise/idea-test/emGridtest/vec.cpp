#include "../../cpp_new_feature/std.h"
#include "Tensor.h"
#include "Curve.h"

class X {
  int i;
  double d[4][4];
};

struct Combine {
  Curve<2, 4> vd;
  double d = 0;
  int* p = nullptr;
  Vec<int, 2> vc[2];
};

template<int Dim>
void f(int N = 256) {
  vector<double> v;
  double vm, rss;
  Box<Dim> ghost(0, N - 1);
  cout << v.capacity() << endl;
  mem_print();
  auto st = clock();
  Tensor<Combine, Dim>* test  = new Tensor<Combine, Dim>(ghost);
  auto ed = clock() - st;
  printf("combine Tensor took me %ld clicks (%f seconds).\n", ed,
         ((float)ed) / CLOCKS_PER_SEC);
  mem_print();
  delete test;

  // sleep(5);
  mem_print();
  st = clock();
  Tensor<Combine*, Dim>* testP = new Tensor<Combine*, Dim>(ghost);
  if constexpr (Dim == 2) {
    loop_box_2(ghost, i, j) if (((i + j) % N) < 4) {
      testP->operator()({i, j}) = new Combine;
    }
  } else if constexpr (Dim == 3) {
    loop_box_3(ghost, i, j, k) if (((i + j) % N) < 4) {
      testP->operator()({i, j, k}) = new Combine;
    }
  }

  ed = clock() - st;
  printf("combine* Tensor took me %ld clicks (%f seconds).\n", ed,
         ((float)ed) / CLOCKS_PER_SEC);
  mem_print();
  if constexpr (Dim == 2) {
    loop_box_2(ghost, i, j) if (testP->operator()({i, j}) != nullptr) {
      delete testP->operator()({i, j});
    }
  } else if constexpr (Dim == 3) {
    loop_box_3(ghost, i, j, k) if (testP->operator()({i, j, k}) != nullptr) {
      delete testP->operator()({i, j ,k});
    }
  }
  delete testP;

  mem_print();
}

int main() {
  f<3>(256);
}