// Дано число N. Определите, сколькими способами можно расставить на доске N × N N
// ферзей, не бьющих друг друга.

#include <iostream>

void combinations(int n, int i, int preColumn, int& result, bool* clearVertical, bool* clearLeftDiagonal, bool* clearRightDiagonal);

int main() {
  int n = 0;
  std::cin >> n;
  bool* clearVertical = new bool[n]();
  bool* clearLeftDiagonal = new bool[(n - 1) * 2 + 1]();
  bool* clearRightDiagonal = new bool[(n - 1) * 2 + 1]();
  for (int i = 0; i < n; ++i) {
    clearVertical[i] = true;
  }
  for (int i = 0; i < (n - 1) * 2 + 1; ++i) {
    clearLeftDiagonal[i] = true;
    clearRightDiagonal[i] = true;
  }
  int i = 0, preColumn = -1, result = 0;
  combinations(n, i, preColumn, result, clearVertical, clearLeftDiagonal, clearRightDiagonal);
  std::cout << result << "\n";
  delete[] clearVertical;
  delete[] clearLeftDiagonal;
  delete[] clearRightDiagonal;
  return 0;
}

void combinations(int n, int i, int preColumn, int& result, bool* clearVertical, bool* clearLeftDiagonal, bool* clearRightDiagonal) {
  if (n == 1) {
    ++result;
    return;
  }
  if (i == n - 1) {
    for (int j = 0; j < n; ++j) {
      if (clearVertical[j] &&
          clearLeftDiagonal[((j + i) / (n - 1)) * (n - 1) + (j + i) % (n - 1)] &&
          clearRightDiagonal[((n - 1 - j + i) / (n - 1)) * (n - 1) + (n - 1 - j + i) % (n - 1)]) {
        ++result;
      }
    }
    clearVertical[preColumn] = true;
    clearLeftDiagonal[((preColumn + i - 1) / (n - 1)) * (n - 1) + (preColumn + i - 1) % (n - 1)] = true;
    clearRightDiagonal[((n - 1 - preColumn + i - 1) / (n - 1)) * (n - 1) + (n - 1 - preColumn + i - 1) % (n - 1)] = true;
    return;
  }
  for (int j = 0; j < n; ++j) {
    if (clearVertical[j] &&
        clearLeftDiagonal[((j + i) / (n - 1)) * (n - 1) + (j + i) % (n - 1)] &&
        clearRightDiagonal[((n - 1 - j + i) / (n - 1)) * (n - 1) + (n - 1 - j + i) % (n - 1)]) {
      clearVertical[j] = false;
      clearLeftDiagonal[((j + i) / (n - 1)) * (n - 1) + (j + i) % (n - 1)] = false;
      clearRightDiagonal[((n - 1 - j + i) / (n - 1)) * (n - 1) + (n - 1 - j + i) % (n - 1)] = false;
      combinations(n, i + 1, j, result, clearVertical, clearLeftDiagonal, clearRightDiagonal);
    }
  }
  if (i != 0) {
    clearVertical[preColumn] = true;
    clearLeftDiagonal[((preColumn + i - 1) / (n - 1)) * (n - 1) + (preColumn + i - 1) % (n - 1)] = true;
    clearRightDiagonal[((n - 1 - preColumn + i - 1) / (n - 1)) * (n - 1) + (n - 1 - preColumn + i - 1) % (n - 1)] = true;
    return;
  }
}