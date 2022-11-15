#include <iostream>

void BuildHeap(int* arr, int size);
void HeapSort(int* arr, int size);
int LeftChild(int pos);
int RightChild(int pos);
void SiftDown(int* arr, int tmpSize, int pos);
void Swap(int& first, int& second);

void Sort(int* arr, const int& size) {
  for (int i = 0; i < size - 1; ++i) {
    int min = 0;
    for (int j = i + 1; j < size; ++j) {
      if (arr[j] < arr[min]) {
        min = j;
      }
    }
    std::swap(arr[i], arr[min]);
  }
}

void Sort(int* arr, const int& size, const int& a, const int&b) {
  int* tmp;
  tmp = new int[b - a + 1];
  for (int i = 0; i < b - a + 1; ++i) {
    tmp[i] = 0;
  }

  for (int i = 0; i < size; ++i) {
    tmp[arr[i]]++;
  }

  for (int i = 0; i < b - a + 1; ++i) {
    if (tmp[i] > 0) {
      for (int j = 0; j < tmp[i]; ++j) {
        std::cout << i << " ";
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  ++n;
  auto* arr = new int[n];
  int size = n - 1;
  for (int i = 1; i <= size; ++i) {
    std::cin >> arr[i];
  }
  HeapSort(arr, size);
  for (int i = 1; i <= size; ++i) {
    std::cout << arr[i] << " ";
  }
  delete[] arr;
  return 0;
}

void BuildHeap(int* arr, int size) {
  for (int i = size / 2; i >= 1; --i) {
    SiftDown(arr, size, i);
  }
}

void HeapSort(int* arr, int size) {
  BuildHeap(arr, size);
  int tmpSize = size - 1;
  for (int i = size; i > 1; --i) {
    Swap(arr[i], arr[1]);
    SiftDown(arr, tmpSize, 1);
    --tmpSize;
  }
}

int LeftChild(int pos) {
  return pos << 1;
}

int RightChild(int pos) {
  return (pos << 1) + 1;
}

void SiftDown(int* arr, int tmpSize, int pos) {
  int left = LeftChild(pos);
  int right = RightChild(pos);
  int biggest = pos;
  if ((left <= tmpSize) && (arr[left] > arr[biggest])) {
    biggest = left;
  }
  if ((right <= tmpSize) && (arr[right] > arr[biggest])) {
    biggest = right;
  }
  if (biggest != pos) {
    Swap(arr[pos], arr[biggest]);
    SiftDown(arr, tmpSize, biggest);
  }
}

void Swap(int& first, int& second) {
  int tmp = first;
  first = second;
  second = tmp;
}