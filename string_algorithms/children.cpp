// — Шрек, ты чего?

// — Не могу поверить, что я скоро стану отцом. Как это получилось?

// Шрек и Фиона не могут неделями успокоить своих шебутных детей. Компьютерные игры еще не 
// придумали, а бабушка с дедушкой вечно заняты, поэтому нашим героям приходится раздавать своих
// детей знакомым на выходные, чтобы хотя бы немного отдохнуть от суеты.
// Больше всего маленькие огры любят проводить время с Волшебным Зеркалом. Зеркало
// примечательно тем, что люди, огры и другие обитатели 3-ки в нем не отражаются. Дети
// расставляют кубики в ряд и ползают вдоль него, таким образом, что всегда видят перед собой 
// N цветных кубиков, но не знают, какие из этих кубиков настоящие, а какие - всего лишь
// отражение в зеркале. Be patient - дети огров, выросшие на болоте, не самые сообразительные
// в мире дети. Помогите им! Выясните, сколько кубиков может быть в комнате с Волшебным
// Зеркалом. Дети видят отражение всех кубиков в зеркале и часть кубиков, которая находится
// перед ними.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int>& ZFunction(const std::vector<int>& cubes, std::vector<int>& z_func);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  std::vector<int> cubes;
  cubes.reserve(2 * n);

  int value = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> value;

    cubes.emplace_back(value);
  }

  for (int i = 0; i < n; ++i) {
    cubes.emplace_back(cubes[n - 1 - i]);
  }

  std::vector<int> z_func;
  z_func = std::move(ZFunction(cubes, z_func));

  std::cout << "\n";

  for (int i = n; i < 2 * n; ++i) {
    if ((z_func[i] % 2 == 0) && (i + z_func[i] == 2 * n)) {
      std::cout << n - z_func[i] / 2 << "\n";
    }
  }

  std::cout << n << "\n";

  return 0;
}

std::vector<int>& ZFunction(const std::vector<int>& cubes, std::vector<int>& z_func) {
  z_func.reserve(cubes.size());
  z_func.emplace_back(cubes.size());

  int size = static_cast<int>(cubes.size());

  int left = 0;
  int right = 0;

  for (int i = 1; i < size; ++i) {

    z_func.emplace_back(std::max(static_cast<int>(0), std::min(right - i, z_func[i - left])));

    while ((i + z_func[i] < size) && (cubes[i + z_func[i]] == cubes[z_func[i]])) {
      ++z_func[i];
    }

    if (i + z_func[i] > right) {
      left = i;
      right = i + z_func[i];
    }
  }

  return z_func;
}