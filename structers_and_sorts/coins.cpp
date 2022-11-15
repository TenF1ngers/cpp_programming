// В Волшебной стране используются монетки достоинством A1, A2,..., AM. Волшебный
// человечек пришел в магазин и обнаружил, что у него есть ровно по две монетки каждого
// достоинства. Ему нужно заплатить сумму N. Напишите программу, определяющую, сможет 
// ли он расплатиться без сдачи.

#include <iostream>

void sort_down(long long* typeOfCoins, long long m);
void select(long long* typeOfCoins, long long* selectedCoins, long long* finalRow, long long& size, long long numInType, long long curSum, long long endInSel, long long n, long long m, bool& is_n, bool& is_moreThanN, bool& is_lessThanN);

int main() {
  long long n = 0, m = 0;
  std::cin >> n >> m;
  long long* typeOfCoins = new long long[m]();
  for (int i = 0; i < m; ++i) {
    std::cin >> typeOfCoins[i];
  }
  sort_down(typeOfCoins, m);
  long long* selectedCoins = new long long[m * 2]();
  long long* finalRow = new long long[m * 2]();
  long long numInType = 0, endInSel = -1, curSum = 0, size = m * 2;
  bool is_n = false, is_moreThanN = false, is_lessThanN = false;
  select(typeOfCoins, selectedCoins, finalRow, size, numInType, curSum, endInSel, n, m, is_n, is_moreThanN, is_lessThanN);
  if (is_n) {
    std::cout << size + 1
              << "\n";
    for (int i = 0; i < size + 1; ++i) {
      std::cout << finalRow[i] << " ";
    }
    std::cout << "\n";
  } else if (is_moreThanN) {
    std::cout << 0
              << "\n";
  } else {
    std::cout << -1
              << "\n";
  }
  delete[] typeOfCoins;
  delete[] selectedCoins;
  delete[] finalRow;
  return 0;
}

void sort_down(long long* typeOfCoins, long long m) {
  int idOfMax = 0;
  for (int i = 0; i < m - 1; ++i) {
    idOfMax = i;
    for (int j = i + 1; j < m; ++j) {
      if (typeOfCoins[j] > typeOfCoins[idOfMax]) {
        idOfMax = j;
      }
    }
    std::swap(typeOfCoins[i], typeOfCoins[idOfMax]);
  }
}

void select(long long* typeOfCoins, long long* selectedCoins, long long* finalRow, long long& size, long long numInType, long long curSum, long long endInSel, long long n, long long m, bool& is_n, bool& is_moreThanN, bool& is_lessThanN) {
  if (curSum == n) {
    if (endInSel < size) {
      size = endInSel;
      for (int i = 0; i < size + 1; ++i) {
        finalRow[i] = selectedCoins[i];
      }
    }
    is_n = true;
    return;
  }
  if ((numInType == m) || (curSum > n)) {
    if (curSum > n) {
      is_moreThanN = true;
    }
    return;
  }
  if ((curSum != 0) && (curSum < n)) {
    is_lessThanN = true;
  }
  for (int i = 2; i >= 0; --i) {
    curSum += typeOfCoins[numInType] * i;
    for (int j = 1; j <= i; ++j) {
      selectedCoins[++endInSel] = typeOfCoins[numInType];
    }
    ++numInType;
    select(typeOfCoins, selectedCoins, finalRow, size, numInType, curSum, endInSel, n, m, is_n, is_moreThanN, is_lessThanN);
    --numInType;
    curSum -= typeOfCoins[numInType] * i;
    endInSel -= i;
  }
}