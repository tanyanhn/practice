#include "std.h"
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

int main() {
  vector<double> v;
  int N = 1000;
  double vm, rss;
  Box<2> ghost(0, N - 1);
  cout << v.capacity() << endl;
  process_mem_usage(vm, rss);
  printf("before start vm: (%lf Mb)  rss: (%lf Mb).\n", vm / 1000, rss / 1000);
  auto st = clock();
  Tensor<Combine, 2>* test  = new Tensor<Combine, 2>(ghost);
  auto ed = clock() - st;
  printf("combine Tensor took me %ld clicks (%f seconds).\n", ed,
         ((float)ed) / CLOCKS_PER_SEC);
  process_mem_usage(vm, rss);
  printf("before start vm: (%lf Mb)  rss: (%lf Mb).\n", vm / 1000, rss / 1000);
  delete test;

  sleep(5);
  process_mem_usage(vm, rss);
  printf("before start vm: (%lf Mb)  rss: (%lf Mb).\n", vm / 1000, rss / 1000);
  st = clock();
  Tensor<Combine*, 2>* testP  = new Tensor<Combine*, 2>(ghost);
  for (auto i = 0; i < N; ++i) {
    for (auto j = 0; j < N; ++j) {
      if (((i + j) % N) < 4) {
        testP->operator()({i, j}) = new Combine;
      }
    }
  }
  ed = clock() - st;
  printf("combine* Tensor took me %ld clicks (%f seconds).\n", ed,
         ((float)ed) / CLOCKS_PER_SEC);
  process_mem_usage(vm, rss);
  printf("before start vm: (%lf Mb)  rss: (%lf Mb).\n", vm / 1000, rss / 1000);
  for (auto i = 0; i < N; ++i) {
    for (auto j = 0; j < N; ++j) {
      if (testP->operator()({i, j}) != nullptr) {
        delete testP->operator()({i, j});
      }
    }
  }
  delete testP;

  process_mem_usage(vm, rss);
  printf("before start vm: (%lf Mb)  rss: (%lf Mb).\n", vm / 1000, rss / 1000);
}