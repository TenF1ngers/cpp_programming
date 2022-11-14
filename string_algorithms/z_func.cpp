// "Шрек, все не так плохо, просто на улице дождь и мрак, и папаша Фионы нанял гада, чтобы тебя убить."
// Дана непустая строка S, длина которой N не превышает 10^6. Будем считать, что элементы строки
// нумеруются с 0 до N − 1
// Для каждой позиции i символа в строке определим Z-блок как наибольшую подстроку, которая
// начинается в этой позиции и совпадает с некоторым началом всей строки S. Значением Z-функции
// Z[i] будем считать длину этого Z-блока. Z-функция используется в различных алгоритмах
// обработки строк. В частности, с её помощью можно быстро решать задачу о поиске вхождения
// одной строке в другую (<<поиск образца в тексте>>). Требуется для всех i от 0 до N−1 вычислить Z[i]

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> ZFunction(const std::string& str);

int main() {
  std::string str;
  std::cin >> str;

  auto z_function = std::move(ZFunction(str));

  for (int i = 0; i < static_cast<int>(z_function.size()); ++i) {
    std::cout << z_function[i] << ' ';
  }

  return 0;
}

std::vector<int> ZFunction(const std::string& str) {
  std::vector<int> z_function;

  z_function.resize(str.size(), 0);
  z_function[0] = static_cast<int>(z_function.size());

  int size = static_cast<int>(z_function.size());

  int left = 0;
  int right = 0;

  for (int i = 1; i < size; ++i) {

    z_function[i] = std::max(static_cast<int>(0), std::min(right - i, z_function[i - left]));

    while ((i + z_function[i] < size) && (str[i + z_function[i]] == str[z_function[i]])) {
      ++z_function[i];
    }

    if (i + z_function[i] > right) {
      left = i;
      right = i + z_function[i];
    }
  }

  return z_function;
}