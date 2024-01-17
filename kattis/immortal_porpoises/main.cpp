#include <iostream>

bool odd(int64_t n) { return n % 2; }

struct matrix {
  int64_t mat[2][2];

  matrix friend operator*(const matrix &a, const matrix &b) {
    matrix c;
    for (int64_t i = 0; i < 2; i++) {
      for (int64_t j = 0; j < 2; j++) {
        c.mat[i][j] = 0;
        for (int64_t k = 0; k < 2; k++) {
          c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
          c.mat[i][j] %= 1'000'000'000;
        }
      }
    }
    return c;
  }
};

matrix matpow(matrix base, int64_t n) {
  matrix res{{{1, 0}, {0, 1}}};

  while (n) {
    if (odd(n)) {
      res = res * base;
    }
    base = base * base;
    n /= 2;
  }

  return res;
}

// O(log n) time
int64_t fib_matrix(int64_t n) {
  matrix base{{{1, 1}, {1, 0}}};
  return matpow(base, n).mat[0][1];
}

int main() {
  int64_t P;
  std::cin >> P;

  while (P--) {
    int64_t K;
    int64_t Y;
    std::cin >> K >> Y;

    std::cout << K << " " << fib_matrix(Y) << "\n";
  };
}
