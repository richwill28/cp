#include <algorithm>
#include <iostream>
#include <utility>

std::pair<int, int> range(int L, int R) {
  // Number of trees left.
  int n = R - L + 1;

  // Only two trees left.
  if (n == 2) {
    std::cout << "Q " << L << " " << L << " " << R << " " << R << "\n";
    std::cout.flush();

    int w1, w2;
    std::cin >> w1 >> w2;

    if (w1 == 1) return std::make_pair(L, L); // Applejack sensed a rustle.
    if (w2 == 1) return std::make_pair(R, R); // Applebloom sensed a rustle.
  }

  // Only three trees left.
  else if (n == 3) {
    // Observe the first two trees.
    std::cout << "Q " << L << " " << L << " " << L + 1 << " " << L + 1 << "\n";
    std::cout.flush();

    int w1, w2;
    std::cin >> w1 >> w2;

    if (w1 == 1) return std::make_pair(L, L);         // Applejack sensed a rustle.
    if (w2 == 1) return std::make_pair(L + 1, L + 1); // Applebloom sensed a rustle.
    if (w2 == 0) return std::make_pair(R, R);         // Applebloom did not sense a rustle.
  }

  else {
    int quo = n / 4;
    int rem = n % 4;

    // Partition the range into four smaller sub-ranges of somewhat equal size.
    int p1 = L + quo + (rem > 0);
    int p2 = p1 + quo + (rem > 1);
    int p3 = p2 + quo + (rem > 2);

    // Layout: l1 ++++ l2 ++++ r1 ++++ r2 ++++ R
    int l1 = L, r1 = std::max(p1, p2 - 1);
    int l2 = p1, r2 = std::max(p2, p3 - 1);

    // Observe the trees according to the layout.
    std::cout << "Q " << l1 << " " << r1 << " " << l2 << " " << r2 << "\n";
    std::cout.flush();

    int w1, w2;
    std::cin >> w1 >> w2;

    if (w1 == 1 && w2 == 0) return std::make_pair(l1, l2 - 1);  // Applejack sensed a rustle but Applebloom did not.
    if (w1 == 1 && w2 == 1) return std::make_pair(l2, r1);      // Applejack sensed a rustle and Applebloom did too.
    if (w1 == 0 && w2 == 1) return std::make_pair(r1 + 1, r2);  // Applejack did not sense a rustle but Applebloom did.
    if (w1 == 0 && w2 == 0) return std::make_pair(r2 + 1, R);   // Applejack did not sense a rustle and Applebloom did not too.
  }
}

int main() {
  int N;
  std::cin >> N;

  int L = 1, R = N;

  while (L < R) {
    L = std::max(1, L - 1);
    R = std::min(N, R + 1);
    std::pair<int, int> res = range(L, R);
    L = res.first;
    R = res.second;
  }

  std::cout << "A " << L << "\n";
  std::cout.flush();
}
