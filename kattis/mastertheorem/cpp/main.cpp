#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <string>

double round(double n) {
  return std::floor(n) + std::floor(10.0 * (n - std::floor(n)) + 0.5) / 10.0;
}

void print_log(double log) {
  if (log == 0.0) {
    return;
  } else if (log == 1.0) {
    std::cout << "log n";
  } else {
    if (log == std::floor(log))
      std::cout << "log^" << std::fixed << std::setprecision(0) << std::floor(log) << " n";
    else
      std::cout << std::fixed << std::setprecision(1) << "log^" << ::round(log)
                << " n";
  }
}

void print_poly(double poly) {
  if (poly == 0.0) {
    return;
  } else if (poly == 1.0) {
    std::cout << "n";
  } else {
    if (poly == std::floor(poly))
      std::cout << "n^" << std::fixed << std::setprecision(0) << std::floor(poly);
    else
      std::cout << "n^" << std::fixed << std::setprecision(1) << ::round(poly);
  }
}

void print(double poly, double log) {
  print_poly(poly);
  std::cout << (poly != 0.0 && log != 0.0 ? " " : "");
  print_log(log);
}

double log(int a, double b) { return log2(a) / log2(b); }

void solve(int a, double b, double c, double d, int k) {
  double c_crit = ::log(a, b);

  bool is_case_1 = d < c_crit;
  bool is_case_2 = d == c_crit;
  bool is_case_3 = d > c_crit;

  if (is_case_1) {
    print(c_crit, 0);

  } else if (is_case_2) {
    if (k >= 0) {
      print(c_crit, k + 1);
    } else if (k == -1) {
      print(c_crit, 0);
      std::cout << " log log n";
    } else if (k < -1) {
      print(c_crit, 0);
    }

  } else if (is_case_3) {
    print(d, k);
  }

  else {
    std::cout << "not applicable";
  }

  std::cout << "\n";
}

int main() {
  int a, k;
  double b, c, d;
  std::cin >> a >> b >> c >> d >> k;
  solve(a, b, c, d, k);
}
