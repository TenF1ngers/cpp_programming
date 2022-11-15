// Если честно, то в жизни мне повезло лишь однажды: когда я встретил вас — моих друзей.

// За окном rain, на душе pain, а смешарики устраивают смотр ледяных скульптур!
// Правила конкурса следующие: статуи выставляются в ряд, каждый смешарик голосует за
// понравившиеся ему бюсты. После этого Копатыч, как единственный независимый судья
// (независимый, потому что проспал весь творческий процесс) пытается определить лучшую
// ледяную композицию.

// По мнению медведя композицией может быть любой подотрезок из ряда скульптур
// (Копатыч сельский житель и плохо разбирается в искусстве). Также Копатыч верит в то,
// что лучшая композиция — композиция, у скульптур в которой суммарное количество голосов
// максимально.

// Помогите Копатычу тем, что напишете программу, которая по его запросу будет говорить
// суммарное количество голосов за ледяную композицию.

#include <iostream>
#include <vector>

void Filling(std::vector<int64_t>& prefix_sum);
void ResultScoreProcess(std::vector<int64_t>& prefix_sum);

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<int64_t> prefix_sum;
  prefix_sum.reserve(n);

  Filling(prefix_sum);

  ResultScoreProcess(prefix_sum);

  return 0;
}

void Filling(std::vector<int64_t>& prefix_sum) {
  int score = 0;
  std::cin >> score;

  prefix_sum.emplace_back(score);

  auto capacity = static_cast<int>(prefix_sum.capacity());
  for (int i = 1; i < capacity; ++i) {
    std::cin >> score;

    prefix_sum.emplace_back(score + prefix_sum[i - 1]);
  }
}

void ResultScoreProcess(std::vector<int64_t>& prefix_sum) {
  int k = 0;
  std::cin >> k;

  int left = 0;
  int right = 0;

  while (k != 0) {
    std::cin >> left >> right;
    --left;
    --right;

    if (left != 0) {
      std::cout << (prefix_sum[right] - prefix_sum[left - 1]) << " ";
    } else {
      std::cout << prefix_sum[right] << " ";
    }

    --k;
  }
}