// Кнут-Моррис-Пратт. Выведите номера символов, начиная с которых строка P входит в строку S, в порядке возрастания.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<size_t> PrefixFunction(const std::string& str);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string str;
  std::cin >> str;

  std::string pattern;
  std::cin >> pattern;

  std::string full_construction = pattern + "#" + str;

  auto prefix = std::move(PrefixFunction(full_construction));

  size_t size = pattern.size();

  for (size_t i = 0; i < prefix.size(); ++i) {
    if (prefix[i] == size) {
      std::cout << i - 2 * size << "\n";
    }
  }

  return 0;
}

std::vector<size_t> PrefixFunction(const std::string& str) {
  std::vector<size_t> prefix(str.size(), 0);

  size_t size = prefix.size();
  size_t k = 0;

  for (size_t i = 1; i < size; ++i) {
    k = prefix[i - 1];

    while ((k > 0) && (str[k] != str[i])) {
      k = prefix[k - 1];
    }

    if (str[k] == str[i]) {
      prefix[i] = k + 1;
    } else {
      prefix[i] = 0;
    }
  }

  return prefix;
}