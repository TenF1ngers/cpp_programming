// Первая строка содержит целое число n (2 ≤ n ≤ 2 ⋅ 10^6 ) — количество пазов в барабане револьвера.

// Во второй строке задана строка a, описывающая состояние барабана револьвера до вращения.

// Строка состоит из n − 1 символа, где ai = 0, если в i-м пазе по часовой стрелке, начиная
// от дула, нет пули, и ai = 1, если есть.

// В третьей строке задана строка b, описывающая состояние барабана револьвера после вращения
// в таком же формате.

// Гарантируется, что входные данные непротиворечивы.

#include <iostream>
#include <string>
#include <vector>

std::vector<int64_t>& ZFunction(const std::string& str, std::vector<int64_t>& z_function);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string main_str;
  std::string random_str;

  int64_t n = 0;

  std::cin >> n;
  std::cin >> main_str;
  std::cin >> random_str; 

  random_str += "#" + main_str + "0" + main_str;

  std::vector<int64_t> z_function;
  z_function = ZFunction(random_str, z_function);

  auto no_shot_0 = false;
  auto shot_0 = false;

  for (int64_t i = n; i < 2 * n; ++i) {
    if (z_function[i] == n - 1) {
      if (random_str[i + z_function[i]] == '0') {
        no_shot_0 = true;
      } else if (random_str[i + z_function[i]] == '1') {
        shot_0 = true;
      }

      break;
    }
  }

  random_str[2 * n - 1] = '1';

  z_function = ZFunction(random_str, z_function);

  bool no_shot_1 = false;
  bool shot_1 = false;

  for (int64_t i = n; i < 2 * n; ++i) {
    if (z_function[i] == n - 1) {
      if (random_str[i + z_function[i]] == '0') {
        no_shot_1 = true;
      } else if (random_str[i + z_function[i]] == '1') {
        shot_1 = true;
      }

      break;
    }
  }

  if (!no_shot_1 && !shot_1) {
    if ((no_shot_0 && shot_0) || (!no_shot_0 && !shot_0)) {
      std::cout << "Random\n";
    } else if (shot_0) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  } else if (!no_shot_0 && !shot_0) {
    if ((no_shot_1 && shot_1) || (!no_shot_1 && !shot_1)) {
      std::cout << "Random\n";
    } else if (shot_1) {
      std::cout << "Yes\n";
    } else {
      std::cout << "No\n";
    }
  } else if ((no_shot_1 && no_shot_0) && (!shot_1 && !shot_0)) {
    std::cout << "No\n";
  } else if ((shot_1 && shot_0) && (!no_shot_1 && !no_shot_0)) {
    std::cout << "Yes\n";
  } else {
    std::cout << "Random\n";
  }

  return 0;
}

std::vector<int64_t>& ZFunction(const std::string& str, std::vector<int64_t>& z_function) {
  z_function.resize(str.size(), 0);
  z_function[0] = static_cast<int64_t>(z_function.size());

  auto size = static_cast<int64_t>(z_function.size());

  int64_t left = 0;
  int64_t right = 0;

  for (int64_t i = 1; i < size; ++i) {

    z_function[i] = std::max(static_cast<int64_t>(0), std::min(right - i, z_function[i - left]));

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