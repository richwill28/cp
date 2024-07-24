#include <iostream>
#include <utility>

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

// O(n) time
int64_t fib(int64_t n) {
  int64_t a = 0;
  int64_t b = 1;
  for (int64_t i = 0; i < n; i++) {
    int64_t tmp = a + b;
    a = b;
    b = tmp;
  }
  return a;
}

// O(log n) time
int64_t fib_matrix(int64_t n) {
  matrix base{{{1, 1}, {1, 0}}};
  return matpow(base, n).mat[0][1];
}

// O(log n) time
std::pair<int64_t, int64_t> fib_doubling(int64_t n) {
  if (n == 0) {
    return {0, 1};
  }

  std::pair<int64_t, int64_t> p = fib_doubling(n / 2);
  int64_t c = p.first * (2 * p.second - p.first);
  int64_t d = p.first * p.first + p.second * p.second;

  if (odd(n)) {
    return {d, c + d};
  }
  return {c, d};
}

int main() {
  int64_t K;
  std::cin >> K;

  auto [A, B] = fib_doubling(K - 1);
  std::cout << A << " " << B << "\n";
}
