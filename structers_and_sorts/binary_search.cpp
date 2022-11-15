#include <ctime>
#include <iostream>

void binarySearch(int* houses, int left, int right, int heightOfK, int& k);
void qSort(int* houses, int n);
void swap(int& first, int& second);

int main() {
  srand(time(nullptr));
  int n = 0;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    arr[i] = rand() % 20;
    std::cout << arr[i] << " ";
  }
  std::cout << "\n";
  qSort(arr, n);
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << "\n";
  int tmp = 0;
  std::cin >> tmp;
  int k = 0;
  binarySearch(arr, 0, n - 1, tmp, k);
  if (k != -1) {
    std::cout << k << "\n";
  } else {
    std::cout << "No" << "\n";
  }
  delete[] arr;
  return 0;
}

void binarySearch(int* houses, int left, int right, int heightOfK, int& k) {
  if (left == right) {
    if (houses[left] == heightOfK) {
      k = left + 1;
      return;
    } else {
      k = -1;
      return;
    }
  }
  int mid = left + (right - left + 1) / 2 - 1;
  if (houses[mid] == heightOfK) {
    binarySearch(houses, mid, mid, heightOfK, k);
  } else {
    if (houses[mid] < heightOfK) {
      binarySearch(houses, mid + 1, right, heightOfK, k);
    } else {
      binarySearch(houses, left, mid - 1, heightOfK, k);
    }
  }
}

void swap(int& first, int& second) {
  int tmp;
  tmp = first;
  first = second;
  second = tmp;
}

void qSort(int* houses, int n) {
  int i = 0, j = n - 1;
  int pivot = houses[n / 2];
  do {
    while (houses[i] < pivot) {
      ++i;
    }
    while (houses[j] > pivot) {
      --j;
    }
    if (i <= j) {
      swap(houses[i], houses[j]);
      ++i;
      --j;
    }
  } while (i <= j);
  if (j >= 0) {
    qSort(houses, j + 1);
  }
  if (i <= n - 1) {
    qSort(&houses[i], n - i);
  }
}