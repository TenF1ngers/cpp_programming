// Дана префикс-функция некоторой строки. Найти лексикографически минимальную строку,
// массив префикс-функции которой совпадет с данным. Алфавит для построения ответа: a-z.

#include <iostream>
#include <string>
#include <vector>

std::string PrefixToStr(const std::vector<size_t>& prefix);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n = 0;
  std::cin >> n;

  std::vector<size_t> prefix(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> prefix[i];
  }

  std::string found_str = PrefixToStr(prefix);

  std::cout << found_str << "\n";

  return 0;
}

std::string PrefixToStr(const std::vector<size_t>& prefix) {
  std::string found_str(prefix.size(), 'a');

  size_t pos = 0;
  std::vector<bool> alphabet(26, false);

  for (size_t i = 1; i < prefix.size(); ++i) {
    if (prefix[i] != 0) {
      found_str[i] = found_str[prefix[i] - 1];
    } else {
      if (prefix[i - 1] == 0) {
        found_str[i] = 'b';
      } else {
        size_t j = i;

        while (prefix[j - 1] > 0) {
          alphabet[found_str[prefix[j - 1]] - 'a'] = true;

          j = prefix[j - 1];
        }

        pos = 1;
        while (alphabet[pos]) {
          ++pos;
        }

        found_str[i] = static_cast<char>('a' + pos);

        for (size_t q = 0; q < 26; ++q) {
          alphabet[q] = false;
        }
      }
    }
  }
  
  return found_str;
}