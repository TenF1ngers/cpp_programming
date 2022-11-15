#include <iostream>
#include <random>

void Swap(int& first, int& second);
void QuickSort1(int* arr, int left, int right);
void QuickSort2(int* arr, int left, int right);
int Partition1(int *arr, int left, int right);
int Partition2(int* arr, int left, int right);
void RandomizeArr(int* arr, int n);

int main() {
  int n = 0;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  RandomizeArr(arr, n);
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i] << ' ';
  }
  std::cout << "\n";
  QuickSort2(arr, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i] << ' ';
  }
  delete[] arr;
  return 0;
}

void RandomizeArr(int* arr, int n) {
  std::random_device rd;
  std::mt19937 mersenne(rd());
  for (int i = 0; i < n; ++i) {
    Swap(arr[i], arr[mersenne() % n]);
  }
}

void Swap(int& first, int& second) {
  int tmp = first;
  first = second;
  second = tmp;
}

int Partition1(int* arr, int left, int right) {
  int pivot_point = left;
  int pivot_value = arr[left];
  for (int i = left + 1; i <= right; ++i) {
    if (arr[i] < pivot_value) {
      ++pivot_point;
      Swap(arr[i], arr[pivot_point]);
    }
  }
  Swap(arr[left], arr[pivot_point]);
  return pivot_point;
}

int Partition2(int* arr, int left, int right) {
  int pivot_value = arr[(left + right) / 2];
  int i = left;
  int j = right;
  while (i <= j) {
    while (arr[i] < pivot_value) {
      ++i;
    }
    while (arr[j] > pivot_value) {
      --j;
    }
    if (i >= j) {
      break;
    }
    Swap(arr[i], arr[j]);
    ++i;
    --j;
  }
  return j;
}

void QuickSort1(int* arr, int left, int right) {
  if (left < right) {
    int pivot = Partition2(arr, left, right);
    QuickSort1(arr, left, pivot);
    QuickSort1(arr, pivot + 1, right);
  }
}

void QuickSort2(int* arr, int left, int right) {
  int pivot_value = arr[right];
  if (left >= right) {
    return;
  }
  int i = left, j = right - 1;
  int p = left - 1, q = right;
  while (i <= j) {
    while (arr[i] < pivot_value) {
      ++i;
    }
    while (arr[j] > pivot_value) {
      --j;
    }
    if (i >= j) {
      break;
    }
    Swap(arr[i], arr[j]);
    if (arr[i] == pivot_value) {
      ++p;
      Swap(arr[i], arr[p]);
    }
    if (arr[j] == pivot_value) {
      --q;
      Swap(arr[j], arr[q]);
    }
    ++i;
    --j;
  }
  Swap(arr[i], arr[right]);
  j = i - 1;
  ++i;
  for (int k = left; k <= p; ++k, --j) {
    Swap(arr[k], arr[j]);
  }
  for (int k = right - 1; k >= q; ++i, --k) {
    Swap(arr[k], arr[i]);
  }
  QuickSort2(arr, left, j);
  QuickSort2(arr, i, right);
}