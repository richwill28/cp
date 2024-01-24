#include <functional>
#include <iostream>
#include <vector>

int64_t num_inversion(std::vector<int64_t> &a) {
  int64_t num = 0;

  std::function<void(int64_t, int64_t)> merge = [&](int64_t l, int64_t r) {
    int64_t m = l + (r - l) / 2;
    int64_t i = l;
    int64_t j = m;

    std::vector<int64_t> tmp;

    while (i < m && j < r) {
      if (a[i] <= a[j]) {
        tmp.push_back(a[i++]);
      } else {
        tmp.push_back(a[j++]);
        num += m - i;
      }
    }

    while (i < m) {
      tmp.push_back(a[i++]);
    }

    while (j < r) {
      tmp.push_back(a[j++]);
    }

    for (int64_t i = l; i < r; i++) {
      a[i] = tmp[i - l];
    }
  };

  std::function<void(int64_t, int64_t)> merge_sort = [&](int64_t l, int64_t r) {
    if (l >= r - 1) {
      return;
    }

    int64_t m = l + (r - l) / 2;
    merge_sort(l, m);
    merge_sort(m, r);
    merge(l, r);
  };

  merge_sort(0, static_cast<int64_t>(a.size()));
  return num;
}

int main() {
  int64_t n;
  std::cin >> n;

  std::vector<int64_t> a;
  a.resize(n);
  for (int64_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::cout << num_inversion(a) << "\n";
}
