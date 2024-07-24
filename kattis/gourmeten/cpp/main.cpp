#include <functional>
#include <iostream>
#include <vector>

void gourmet(int64_t M, int64_t N, std::vector<int64_t> &T) {
  std::vector<int64_t> res(M + 1, -1);
  res[0] = 1;

  std::function<int64_t(int64_t)> dp = [&](int64_t i) {
    if (i < 0) {
      return static_cast<int64_t>(0);
    }

    if (res[i] != -1) {
      return res[i];
    }

    res[i] = 0;
    for (int64_t j = 0; j < N; j++) {
      res[i] += dp(i - T[j]);
    }
    return res[i];
  };

  std::cout << dp(M) << "\n";
}

int main() {
  int64_t M, N;
  std::cin >> M >> N;

  std::vector<int64_t> T(N);
  for (int64_t i = 0; i < N; i++) {
    std::cin >> T[i];
  }

  gourmet(M, N, T);
}
