#include <cstring>
#include <iostream>

void fromDecimalToBinary(char* val, int& j, int& firstZeroInVal);

int main() {
  char str[256] = {}, val[256] = {};
  std::cin.getline(str, 256);
  int len = (int)strlen(str), j = 0, firstZeroInVal = -1;
  for (int i = 0; i < len; ++i) {
    if ((str[i] < '0') || (str[i] > '9')) {
      std::cout << str[i];
    } else {
      while ((str[i] >= '0') && (str[i] <= '9') && (i < len)) {
        val[j++] = str[i++];
      }
      fromDecimalToBinary(val, j, firstZeroInVal);
      if (i < len) {
        std::cout << str[i];
      }
      j = 0;
      firstZeroInVal = -1;
    }
  }
  return 0;
}

void fromDecimalToBinary(char* val, int& j, int& firstZeroInVal) {
  if ((val[j - 1] == '1') && (firstZeroInVal + 1 == j - 1)) {
    std::cout << "1";
  } else {
    int remainder = 0, tmpRem = 0, preNum = 0, notZeroInVal = j - 1;
    for (int i = firstZeroInVal + 1; i < j; ++i) {
      preNum = val[i] - '0';
      val[i] = (char)('0' + (val[i] - '0' + tmpRem * 10) / 2);
      if (val[i] != '0') {
        notZeroInVal = i;
      }
      tmpRem = preNum % 2;
      if ((val[i] == '0') && (i < notZeroInVal)) {
        firstZeroInVal = i;
      }
    }
    remainder = tmpRem;
    fromDecimalToBinary(val, j, firstZeroInVal);
    std::cout << remainder;
  }
}