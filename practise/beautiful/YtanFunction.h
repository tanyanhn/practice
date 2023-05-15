#include <cstddef>
#include <vector>

template <typename T>
std::vector<std::vector<T>> yTanPartition(
    const std::vector<std::vector<T>>& connected) {
  std::vector<std::vector<T>> ret;
  auto size = connected.size();
  std::vector<int> mark(size, 0);

  for (size_t i = 0; i < size; ++i) {
    if (mark[i] == 1) {
      continue;
    }
    std::vector<size_t> find;
    std::vector<size_t> part;
    find.push_back(i);
    mark[i] = 1;
    while (!find.empty()) {
      auto fi = find.back();
      find.pop_back();
      part.push_back(fi);
      for (size_t j = i + 1; j < size; ++j) {
        if (mark[j] == 0 && connected[fi][j] != 0) {
          find.push_back(j);
          mark[j] = 1;
        }
      }
    }
    ret.emplace_back(part.begin(), part.end());
  }

  return ret;
}