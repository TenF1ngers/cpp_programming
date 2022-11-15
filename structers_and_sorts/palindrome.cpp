// Палиндромом называется строка, которая, после удаления из нее всех пробелов и знаков
// препинания, читается одинаково справа налево и слева направо.

// По заданной строке нужно определить, можно ли с помощью одного изменения (замены
// символа, удаления или добавления) превратить ее в палиндром. В палиндроме учитываются
// только латинские буквы без учета регистра. То есть строки "aba, cA !Ba" и "abacaba"
// задают один и тот же палиндром.

#include <cstring>
#include <iostream>

int main() {
  char str[100001] = {}, sentence[10001] = {};
  std::cin.getline(str, 100001);
  int lenSent = 0, len = (int)strlen(str);
  for (int i = 0; i < len; ++i) {
    if (((str[i] >= 'a') && (str[i] <= 'z')) || ((str[i] >= 'A') && (str[i] <= 'Z'))) {
      sentence[lenSent++] = (char)toupper(str[i]);
    }
  }
  bool is_palindrome = false;
  int idOfReplace = -1, countOfDiscrepancies = 0;
  for (int i = (lenSent / 2) - 1; i >= 0; --i) {
    if (sentence[i] != sentence[lenSent - 1 - i]) {
      ++countOfDiscrepancies;
      idOfReplace = i;
    }
    if (countOfDiscrepancies > 1) {
      break;
    }
  }
  if (countOfDiscrepancies == 1) {
    std::cout << "YES"
              << "\n";
    for (int i = 0; i < lenSent; ++i) {
      if (i == idOfReplace) {
        std::cout << sentence[lenSent - 1 - i];
      } else {
        std::cout << sentence[i];
      }
    }
  } else {
    for (int i = 0; i < lenSent; ++i) {
      countOfDiscrepancies = 0;
      for (int j = (lenSent + 1) / 2 - 1; j >= 0; --j) {
        if ((j == i) || (lenSent - j == i)) {
          continue;
        }
        if (i < j) {
          if (sentence[j - 1] != sentence[lenSent - j - 1]) {
            ++countOfDiscrepancies;
          }
        } else if ((i > j) && (i < lenSent - j)) {
          if (sentence[j] != sentence[lenSent - j - 1]) {
            ++countOfDiscrepancies;
          }
        } else {
          if (sentence[j] != sentence[lenSent - j]) {
            ++countOfDiscrepancies;
          }
        }
        if (countOfDiscrepancies != 0) {
          break;
        }
      }
      if (countOfDiscrepancies == 0) {
        std::cout << "YES"
                  << "\n";
        for (int t = 0; t < lenSent; ++t) {
          if (t == i) {
            std::cout << sentence[lenSent - i - 1] << sentence[t];
          } else {
            std::cout << sentence[t];
          }
        }
        is_palindrome = true;
        break;
      }
    }
    if (!is_palindrome) {
      std::cout << "NO"
                << "\n";
    }
  }
  return 0;
}