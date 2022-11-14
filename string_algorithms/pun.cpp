// Шрек и Кот в сапогах наконец-то нашли общий язык и теперь мучают Осла новыми каламбурами.
// Схема очень проста и именно поэтому просто невыносима - n слов склеиваются в одно, по
// следующему правилу: если два слова идут подряд, то удаляется самый длинный префикс второго
// слова, который совпадает с суффиксом первого слова. Например, слова "каламбур" и "буря"
// склеиваются в "каламбурю" (грозящую погрести под собой Осла). Каламбур склеивается слева
// направо (т.е. сначала склеиваются первые два слова, потом результат с третьим, и так далее).
// Напишите программу, которая поможет культивировать это развлечение.

#include <iostream>
#include <string>
#include <vector>

std::string CreatePun(std::string& tmp_str, std::vector<size_t>& prefix_func);
std::vector<size_t>& PrefixFunction(const std::string& str, std::vector<size_t>& prefix_func);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  std::cin >> n;

  std::string pun;
  std::string tmp_str;
  std::vector<size_t> prefix_func;

  std::cin >> pun;
  --n;

  for (int i = 0; i < n; ++i) {
    std::cin >> tmp_str;

    if (pun.size() > tmp_str.size()) {
      tmp_str += "#";

      for (auto i = pun.size() - tmp_str.size(); i < pun.size(); ++i) {
        tmp_str += pun[i];
      }
    } else {
      tmp_str += "#" + pun;
    }

    prefix_func = PrefixFunction(tmp_str, prefix_func);

    pun += CreatePun(tmp_str, prefix_func);
  }

  std::cout << pun << "\n";

  return 0;
}

std::string CreatePun(std::string& tmp_str, std::vector<size_t>& prefix_func) {
  std::string intermediate_result;
  auto i = prefix_func[prefix_func.size() - 1]; 

  while (tmp_str[i] != '#') {
    intermediate_result += tmp_str[i];

    ++i;
  }

  return intermediate_result;
}

std::vector<size_t>& PrefixFunction(const std::string& str, std::vector<size_t>& prefix_func) {
  prefix_func.resize(str.size(), 0);

  size_t size = prefix_func.size();
  size_t k = 0;

  for (size_t i = 1; i < size; ++i) {
    k = prefix_func[i - 1];

    while ((k > 0) && (str[k] != str[i])) {
      k = prefix_func[k - 1];
    }

    if (str[k] == str[i]) {
      prefix_func[i] = k + 1;
    } else {
      prefix_func[i] = 0;
    }
  }
  
  return prefix_func;
}