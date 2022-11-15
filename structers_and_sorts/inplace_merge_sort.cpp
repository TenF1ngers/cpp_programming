#include <iostream>
#include <ctime>
#include <random>

void BinarySearch(int* pArr, int n, int* pBeg, int* pEnd, int key, int& pOfKey, bool findLB);
void InplaceMerge(int* first, int n, int* second, int m);
void MergeSort(int* arr, int size);
void Swap(int* first, int* second);
void SwapArrays(int* first, int n, int* second, int m);

int main() {
  srand(time(nullptr));
  int n = 0;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    arr[i] = rand() % n + 1;
  }
  MergeSort(arr, n);
  bool is_sort = true;
  for (int i = 0; i < n - 1; ++i) {
    if (arr[i] > arr[i + 1]) {
      is_sort = false;
    }
  }
  std::cout << is_sort << "\n";
  delete[] arr;
  return 0;
}

void BinarySearch(int* pArr, int n, int* pBeg, int* pEnd, int key, int& pOfKey, bool findLB) {
  if (pBeg == pEnd) {
    if (findLB) {
      if (*pBeg >= key) {
        pOfKey = (int)(pBeg - pArr);
      } else {
        if (pBeg < pArr + n - 1) {
          pOfKey = (int)(pBeg - pArr) + 1;
        }
      }
    } else {
      if (*pBeg > key) {
        pOfKey = (int)(pBeg - pArr);
      } else if (*pBeg == key) {
        while ((pBeg + 1 <= pArr + n - 1) && (*(pBeg + 1) == key)) {
          ++pBeg;
        }
        if (pBeg < pArr + n - 1) {
          pOfKey = (int)(pBeg - pArr) + 1;
        }
      } else {
        if (pBeg != pArr + n - 1) {
          pOfKey = (int)(pBeg - pArr) + 1;
        }
      }
    }
    return;
  }
  int* mid = pBeg + (pEnd - pBeg) / 2;
  if ((findLB) && (*mid == key)) {
    pOfKey = (int)(mid - pArr);
  } else if ((!findLB) && (*mid == key)) {
    while ((mid + 1 <= pEnd) && (*(mid + 1) == key)) {
      ++mid;
    }
    if (mid < pEnd) {
      pOfKey = (int)(mid - pArr) + 1;
    }
  } else {
    if (*mid > key) {
      if (mid != pBeg) {
        BinarySearch(pArr, n, pBeg, mid - 1, key, pOfKey, findLB);
      } else {
        pOfKey = (int)(pBeg - pArr);
      }
    } else {
      if (mid != pEnd) {
        BinarySearch(pArr, n, mid + 1, pEnd, key, pOfKey, findLB);
      }
    }
  }
}

void InplaceMerge(int* first, int n, int* second, int m) {
  if ((n == 0) || (m == 0)) {
    return;
  }
  if ((n == 1) && (m == 1)) {
    if (*first > *second) {
      Swap(first, second);
    }
    return;
  }
  bool findLB = false;
  if (n >= m) {
    findLB = true;
    int x = n / 2, lowerBound = -1;
    BinarySearch(second, m, second, second + m - 1, *(first + x), lowerBound, findLB);
    if (lowerBound != -1) {
      while ((*(second + lowerBound - 1) == *(first + x)) && (second + lowerBound - 1 >= second)) {
        --lowerBound;
      }
      SwapArrays(first + x, n - x, second, lowerBound);
      InplaceMerge(first, x, first + x , lowerBound);
      InplaceMerge(first + x + 1 + lowerBound, n - x - 1, first + n + lowerBound, m - lowerBound);
    } else {
      SwapArrays(first + x, n - x, second, m);
      InplaceMerge(first, x, first + x, m);
    }
  } else {
    int x = m / 2, upperBound = -1;
    BinarySearch(first, n, first, first + n - 1, *(second + x), upperBound, findLB);
    if (upperBound != -1) {
      while ((*(first + upperBound - 1) > *(second + x)) && (first + upperBound - 1 >= first)) {
        --upperBound;
      }
      SwapArrays(first + upperBound, n - upperBound, second, x + 1);
      InplaceMerge(first, upperBound, first + upperBound , x);
      InplaceMerge(first + upperBound + x + 1, n - upperBound, first + n + x + 1, m - x - 1);
    } else {
      InplaceMerge(first, n, first + n, x);
    }
  }
}

void MergeSort(int* arr, int size) {
  if (size == 1) {
    return;
  }
  MergeSort(arr, size / 2);
  MergeSort(arr + size / 2, size - size / 2);
  InplaceMerge(arr, size / 2, arr + size / 2, size - size / 2);
}

void Swap(int* first, int* second) {
  int tmp = *first;
  *first = *second;
  *second = tmp;
}

void SwapArrays(int* first, int n, int* second, int m) {
  for (int* point = first + n / 2 - 1; point >= first; --point) {
    Swap(point, first + ((first + n - 1) - point));
  }
  for (int* point = second + m / 2 - 1; point >= second; --point) {
    Swap(point, second + ((second + m - 1) - point));
  }
  for (int* point = first + (n + m) / 2 - 1; point >= first; --point) {
    Swap(point, first + ((first + (n + m) - 1) - point));
  }
}