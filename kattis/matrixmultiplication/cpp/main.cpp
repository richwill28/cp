#include <iostream>
#include <random>
#include <vector>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distrib(0, 1);

void multiply(const std::vector<std::vector<int>> &M, const std::vector<int> &r,
              std::vector<int> &res) {
  for (size_t i = 0; i < M.size(); i++) {
    int Mi = 0;
    for (size_t j = 0; j < r.size(); j++) {
      Mi += M[i][j] * r[j];
    }
    res.push_back(Mi);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int TC;
  std::cin >> TC;

  while (TC--) {

    int n, x, y, m;
    std::cin >> n >> x >> y >> m;

    std::vector<std::vector<int>> A(n, std::vector<int>(x));
    std::vector<std::vector<int>> B(y, std::vector<int>(m));
    std::vector<std::vector<int>> C(n, std::vector<int>(m));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < x; j++) {
        std::cin >> A[i][j];
      }
    }

    for (int i = 0; i < y; i++) {
      for (int j = 0; j < m; j++) {
        std::cin >> B[i][j];
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        std::cin >> C[i][j];
      }
    }

    int k = 12;

    if (x != y) {
      goto na;
    }

    while (k--) {
      std::vector<int> r;
      for (int i = 0; i < m; i++) {
        r.push_back(distrib(gen));
      }

      std::vector<int> Br;
      multiply(B, r, Br);

      std::vector<int> ABr;
      multiply(A, Br, ABr);

      std::vector<int> Cr;
      multiply(C, r, Cr);

      for (int i = 0; i < n; i++) {
        if (ABr[i] != Cr[i]) {
          goto wa;
        }
      }
    }

    std::cout << "AC\n";
    continue;

  wa:
    std::cout << "WA\n";
    continue;

  na:
    std::cout << "Inner matrix dimensions must agree\n";
    continue;
  }
}
