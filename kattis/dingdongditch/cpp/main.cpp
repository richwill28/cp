#include <algorithm>
#include <iostream>
#include <vector>

void dingdongditch(int64_t N, int64_t Q, std::vector<int64_t> &A,
                   std::vector<int64_t> &B) {
  std::sort(A.begin(), A.end());

  std::vector<int64_t> psum(N);
  psum[0] = A[0];
  for (int64_t i = 1; i < N; i++) {
    psum[i] = psum[i - 1] + A[i];
  }

  for (int64_t i = 0; i < Q; i++) {
    std::cout << psum[B[i] - 1] << "\n";
  }
}

int main() {
  int64_t N, Q;
  std::cin >> N >> Q;

  std::vector<int64_t> A(N);
  for (int64_t i = 0; i < N; i++) {
    std::cin >> A[i];
  }

  std::vector<int64_t> B(Q);
  for (int64_t i = 0; i < Q; i++) {
    std::cin >> B[i];
  }

  dingdongditch(N, Q, A, B);
}
