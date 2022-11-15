#include <iostream>

void mergeSort(int* left, const int* right);
void merge(int* left, const int* right);
bool isSimilar(int* firstArr, int firstLen, int* secondArr, int secondLen);

int main() {
  int firstLen = 0;
  std::cin >> firstLen;
  int* firstArr = new int[firstLen];
  for (int i = 0; i < firstLen; ++i) {
    std::cin >> firstArr[i];
  }
  int secondLen = 0;
  std::cin >> secondLen;
  int* secondArr = new int[secondLen];
  for (int i = 0; i < secondLen; ++i) {
    std::cin >> secondArr[i];
  }
  mergeSort(firstArr, firstArr + firstLen - 1);
  mergeSort(secondArr, secondArr + secondLen - 1);
  bool similar = isSimilar(firstArr, firstLen, secondArr, secondLen);
  if (similar) {
    std::cout << "YES"
              << "\n";
  } else {
    std::cout << "NO"
              << "\n";
  }
  delete[] firstArr;
  delete[] secondArr;
  return 0;
}

bool isSimilar(int* firstArr, int firstLen, int* secondArr, int secondLen) {
  bool similar = true;
  int tmp = 0;
  int *iterFirst = firstArr, *iterSecond = secondArr;
  int *iterFirstOfEnd = firstArr + firstLen - 1,
      *iterSecondOfEnd = secondArr + secondLen - 1;
  while ((iterFirst <= iterFirstOfEnd) && (iterSecond <= iterSecondOfEnd)) {
    if (*iterFirst == *iterSecond) {
      tmp = *iterFirst;
      while ((iterFirst <= iterFirstOfEnd) && (*iterFirst == tmp)) {
        ++iterFirst;
      }
      while ((iterSecond <= iterSecondOfEnd) && (*iterSecond == tmp)) {
        ++iterSecond;
      }
    } else {
      similar = false;
      break;
    }
  }
  if (similar) {
    if ((iterFirst <= iterFirstOfEnd) || (iterSecond <= iterSecondOfEnd)) {
      similar = false;
    }
  }
  return similar;
}

void mergeSort(int* left, const int* right) {
  if (left == right) {
    return;
  }
  int* mid = left + (right - left) / 2;
  mergeSort(left, mid);
  mergeSort(mid + 1, right);
  merge(left, right);
}

void merge(int* left, const int* right) {
  if (left == right) {
    return;
  }
  int* mid = left + (right - left) / 2;
  int *iterLeft = left, *iterRight = mid + 1;
  int len = right - left + 1;
  int* tmpArr = new int[len];
  int j = 0;
  while ((iterLeft <= mid) && (iterRight <= right)) {
    if (*iterLeft <= *iterRight) {
      tmpArr[j++] = *iterLeft++;
    } else {
      tmpArr[j++] = *iterRight++;
    }
  }
  while (iterLeft <= mid) {
    tmpArr[j++] = *iterLeft++;
  }
  while (iterRight <= right) {
    tmpArr[j++] = *iterRight++;
  }
  iterLeft = left;
  for (j = 0; j < len; ++j) {
    *iterLeft++ = tmpArr[j];
  }
  delete[] tmpArr;
}