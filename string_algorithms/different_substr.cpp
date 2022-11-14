// Подсчитайте число различных подстрок строки S.

#include <iostream>
#include <string>
#include <vector>

size_t MaxPrefixFunction(const std::string& runner, size_t size);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string str;
  std::cin >> str;

  std::string runner;
  runner.resize(str.size());
  runner[0] = str[0];

  size_t count = 1;
  size_t max = 0;

  for (size_t i = 1; i < str.size(); ++i) {
    runner[i] = str[i];

    max = MaxPrefixFunction(runner, i + 1);

    count += i + 1 - max;
  }

  std::cout << count << "\n";

  return 0;
}

size_t MaxPrefixFunction(const std::string& runner, size_t size) {
  std::vector<size_t> prefix(size, 0);

  std::string temporary;
  temporary.resize(size);

  for (size_t i = 0; i < size; ++i) {
    temporary[i] = runner[size - i - 1];
  }

  size_t k = 0;
  size_t max = 0;

  for (size_t i = 1; i < size; ++i) {
    k = prefix[i - 1];

    while ((k > 0) && (temporary[k] != temporary[i])) {
      k = prefix[k - 1];
    }

    if (temporary[k] == temporary[i]) {
      prefix[i] = k + 1;

      if (prefix[i] > max) {
        max = prefix[i];
      }
    } else {
      prefix[i] = 0;
    }
  }

  return max;
}