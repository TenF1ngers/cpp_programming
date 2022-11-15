#include <cstring>
#include <iostream>

struct Enrollee {
  char* name;
  char* surname;
  double score;
};

void LBBinarySearch(Enrollee* pArr, int n, Enrollee* pBeg, Enrollee* pEnd, double key, int& pOfKey);
void UBBinarySearch(Enrollee* pArr, int n, Enrollee* pBeg, Enrollee* pEnd, double key, int& pOfKey);
void InplaceMerge(Enrollee* first, int n, Enrollee* second, int m);
void MergeSort(Enrollee* arr, int size);
void Swap(Enrollee* first, Enrollee* second);
void SwapArrays(Enrollee* first, int n, Enrollee* second, int m);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  auto* arr = new Enrollee[n];
  int inf = 0, math = 0, rus = 0;
  for (int i = 0; i < n; ++i) {
    arr[i].name = new char[100001];
    arr[i].surname = new char[100001];
    std::cin >> arr[i].name >> arr[i].surname;
    std::cin >> inf >> math >> rus;
    arr[i].score = (double)(inf + math + rus) / 2.;
  }
  MergeSort(arr, n);
  int len = 0;
  for (int i = 0; i < n; ++i) {
    len = (int)strlen(arr[i].name);
    for (int j = 0; j < len; ++j) {
      std::cout << arr[i].name[j];
    }
    std::cout << " ";
    len = (int)strlen(arr[i].surname);
    for (int j = 0; j < len; ++j) {
      std::cout << arr[i].surname[j];
    }
    std::cout << "\n";
  }
  for (int i = 0; i < n; ++i) {
    delete[] arr[i].name;
    delete[] arr[i].surname;
  }
  delete[] arr;
  return 0;
}

void LBBinarySearch(Enrollee* pArr, int n, Enrollee* pBeg, Enrollee* pEnd, double key, int& pOfKey) {
  if (pBeg == pEnd) {
    if (pBeg->score >= key) {
      while ((pBeg < pArr + n - 1) && ((pBeg + 1)->score >= key)) {
        ++pBeg;
      }
      pOfKey = (int)(pBeg - pArr);
    } else {
      if (pBeg != pArr) {
        while ((pBeg > pArr) && ((pBeg - 1)->score < key)) {
          --pBeg;
        }
        if (pBeg > pArr) {
          pOfKey = (int)(pBeg - pArr) - 1;
        }
      }
    }
    return;
  }
  Enrollee* mid = pBeg + (pEnd - pBeg) / 2;
  if (mid->score == key) {
    while ((mid < pArr + n - 1) && ((mid + 1)->score >= key)) {
      ++mid;
    }
    pOfKey = (int)(mid - pArr);
  } else if (mid->score > key) {
    LBBinarySearch(pArr, n, mid + 1, pEnd, key, pOfKey);
  } else {
    if (mid != pBeg) {
      LBBinarySearch(pArr, n, pBeg, mid - 1, key, pOfKey);
    } else {
      LBBinarySearch(pArr, n, pBeg - 1, mid - 1, key, pOfKey);
    }
  }
}

void UBBinarySearch(Enrollee* pArr, int n, Enrollee* pBeg, Enrollee* pEnd, double key, int& pOfKey) {
  if (pBeg == pEnd) {
    if (pBeg->score > key) {
      while ((pBeg < pArr + n - 1) && ((pBeg + 1)->score > key)) {
        ++pBeg;
      }
      pOfKey = (int)(pBeg - pArr);
    } else {
      if (pBeg != pArr) {
        while ((pBeg > pArr) && ((pBeg - 1)->score <= key)) {
          --pBeg;
        }
        if (pBeg > pArr) {
          pOfKey = (int)(pBeg - pArr) - 1;
        }
      }
    }
    return;
  }
  Enrollee* mid = pBeg + (pEnd - pBeg) / 2;
  if (mid->score == key) {
    while ((mid > pArr) && ((mid - 1)->score == key)) {
      --mid;
    }
    if (mid > pArr) {
      pOfKey = (int)(mid - pArr) - 1;
    }
  } else if (mid->score > key) {
    UBBinarySearch(pArr, n, mid + 1, pEnd, key, pOfKey);
  } else {
    if (mid != pBeg) {
      UBBinarySearch(pArr, n, pBeg, mid - 1, key, pOfKey);
    } else {
      UBBinarySearch(pArr, n, pBeg - 1, mid - 1, key, pOfKey);
    }
  }
}

void InplaceMerge(Enrollee* first, int n, Enrollee* second, int m) {
  if ((n == 0) || (m == 0)) {
    return;
  }
  if ((n == 1) && (m == 1)) {
    if (first->score < second->score) {
      Swap(first, second);
    }
    return;
  }
  if (second->score <= (first + n - 1)->score) {
    return;
  }
  if (n <= m) {
    int x = m / 2, lowerBound = -1;
    LBBinarySearch(first, n, first, first + n - 1, (second + x)->score, lowerBound);
    if (lowerBound != -1) {
      SwapArrays(first + lowerBound + 1, n - lowerBound - 1, second, x + 1);
      InplaceMerge(first, lowerBound + 1, first + lowerBound + 1, x);
      if (x != m - 1) {
        InplaceMerge(first + x + 2 + lowerBound, n - lowerBound - 1, first + x + n + 1, m - x - 1);
      }
    } else {
      SwapArrays(first, n, second, x + 1);
      InplaceMerge(first + x + 1, n, first + x + n + 1, m - x - 1);
    }
  } else {
    int x = n / 2, upperBound = -1;
    UBBinarySearch(second, m, second, second + m - 1, (first + x)->score, upperBound);
    if (upperBound != -1) {
      SwapArrays(first + x, n - x, second, upperBound + 1);
      InplaceMerge(first, x, first + x, upperBound + 1);
      if (x != n - 1) {
        InplaceMerge(first + upperBound + x + 2, n - x - 1, first + n + upperBound + 1, m - upperBound - 1);
      }
    } else {
      InplaceMerge(first + x + 1, n - x - 1, second, m);
    }
  }
}

void MergeSort(Enrollee* arr, int size) {
  if (size <= 1) {
    return;
  }
  MergeSort(arr + size / 2, size - size / 2);
  MergeSort(arr, size / 2);
  InplaceMerge(arr, size / 2, arr + size / 2, size - size / 2);
}

void Swap(Enrollee* first, Enrollee* second) {
  double tmp = 0.;
  tmp = first->score;
  first->score = second->score;
  second->score = tmp;
  char* tmpStr;
  tmpStr = first->name;
  first->name = second->name;
  second->name = tmpStr;
  tmpStr = first->surname;
  first->surname = second->surname;
  second->surname = tmpStr;
}

void SwapArrays(Enrollee* first, int n, Enrollee* second, int m) {
  for (Enrollee* point = first + n / 2 - 1; point >= first; --point) {
    Swap(point, first + ((first + n - 1) - point));
  }
  for (Enrollee* point = second + m / 2 - 1; point >= second; --point) {
    Swap(point, second + ((second + m - 1) - point));
  }
  for (Enrollee* point = first + (n + m) / 2 - 1; point >= first; --point) {
    Swap(point, first + ((first + (n + m) - 1) - point));
  }
}