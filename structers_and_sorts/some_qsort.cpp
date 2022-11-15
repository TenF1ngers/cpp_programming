#include <iostream>

void Swap(unsigned long long& first, unsigned long long& second);
void QuickSort(unsigned long long* sequence, int n);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  int n = 0, k = 0;
  std::cin >> n >> k;
  auto* sequence = new unsigned long long[n]();
  std::cin >> sequence[0] >> sequence[1];
  int val = 10004321;
  if (k <= 2) {
    std::cout << sequence[k - 1] << "\n";
  } else {
    for (int i = 2; i < n; ++i) {
      sequence[i] = (sequence[i - 1] * 123 + sequence[i - 2] * 45) % val;
    }
    QuickSort(sequence, n);
    std::cout << sequence[k - 1] << "\n";
  }
  delete[] sequence;
  return 0;
}

void Swap(unsigned long long& first, unsigned long long& second) {
  unsigned long long tmp = first;
  first = second;
  second = tmp;
}

void QuickSort(unsigned long long* sequence, int n) {
  int i = 0, j = n - 1;
  unsigned long long pivot = sequence[n / 2];
  do {
    while (sequence[i] < pivot) {
      ++i;
    }
    while (sequence[j] > pivot) {
      --j;
    }
    if (i <= j) {
      Swap(sequence[i], sequence[j]);
      ++i;
      --j;
    }
  } while (i <= j);
  if (i < n) {
    QuickSort(&sequence[i], n - i);
  }
  if (j >= 0) {
    QuickSort(sequence, j + 1);
  }
}w