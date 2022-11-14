// Витя хочет придумать новую игру с числами. В этой игре от игроков требуется
// преобразовывать четырехзначные числа не содержащие нулей при помощи следующего
// разрешенного набора действий:

// Можно увеличить первую цифру числа на 1, если она не равна 9.

// Можно уменьшить последнюю цифру на 1, если она не равна 1.

// Можно циклически сдвинуть все цифры на одну вправо.

// Можно циклически сдвинуть все цифры на одну влево.

// Например, применяя эти правила к числу 1234 можно получить числа 2234, 1233, 4123 и
// 2341 соответственно. Точные правила игры Витя пока не придумал, но пока его интересует
// вопрос, как получить из одного числа другое за минимальное количество операций.

#include <iostream>
#include <unordered_set>
#include <vector>

class Graph {
 private:
  struct Node {
    int from_;
    int condition_;
    int count_;

    Node(const int& from, const int& condition, const int& count) : from_(from), condition_(condition), count_(count) {
    }
  };

  std::vector<Node> vertexes_;
  std::unordered_set<int> having_;

  int FirstOperation(const int& value) {
    int result = 0;
    int whole_part = value / 1000;

    if (whole_part != 9) {
      result = value + 1000;
    } else {
      result = value;
    }

    return result;
  }

  int SecondOperation(const int& value) {
    int result = 0;
    int last_digit = value % 10;

    if (last_digit != 1) {
      result = value - 1;
    } else {
      result = value;
    }

    return result;
  }

  int ThirdOperation(const int& value) {
    int result = 0;

    result = (value % 10) * 1000;
    result += (value / 1000) * 100;
    result += ((value - (value / 1000) * 1000) / 100) * 10;
    result += ((value - (value / 1000) * 1000) - ((value - (value / 1000) * 1000) / 100) * 100) / 10;

    return result;
  }

  int FourthOperation(const int& value) {
    int result = 0;

    result += value / 1000;
    result += value % 10 * 10;
    result += (value - (value / 1000) * 1000) / 100 * 1000;
    result += ((value - (value / 1000) * 1000) - ((value - (value / 1000) * 1000) / 100) * 100) / 10 * 100;

    return result;
  }

  void PrintWay(int pos) {
    std::cout << vertexes_[pos].count_ + 1 << "\n";

    std::vector<int> way;
    way.reserve(vertexes_[pos].count_ + 1);

    while (vertexes_[pos].count_ != 0) {
      way.emplace_back(vertexes_[pos].condition_);

      pos = vertexes_[pos].from_;
    }
    way.emplace_back(vertexes_[pos].condition_);

    for (ssize_t i = way.size() - 1; i >= 0; --i) {
      std::cout << way[i] << "\n";
    }
  }

 public:
  // Build using BFS-idiom
  Graph(const int& first, const int& second) {
    vertexes_.emplace_back(Node(-1, first, 0));
    having_.emplace(first);

    bool is_find = false;
    int pos = 0;

    int value_1 = 0;
    int value_2 = 0;
    int value_3 = 0;
    int value_4 = 0;

    int node = 0;
    int runner = 0;

    while (!is_find) {
      runner = node;

      while (runner < static_cast<int>(vertexes_.size())) {
        value_1 = FirstOperation(vertexes_[runner].condition_);
        value_2 = SecondOperation(vertexes_[runner].condition_);
        value_3 = ThirdOperation(vertexes_[runner].condition_);
        value_4 = FourthOperation(vertexes_[runner].condition_);

        if (value_1 != vertexes_[runner].condition_) {
          if (value_1 == second) {
            vertexes_.emplace_back(Node(runner, value_1, vertexes_[runner].count_ + 1));
            pos = vertexes_.size() - 1;

            is_find = true;

            break;
          }
        }

        if (value_2 != vertexes_[runner].condition_) {
          if (value_2 == second) {
            vertexes_.emplace_back(Node(runner, value_2, vertexes_[runner].count_ + 1));
            pos = vertexes_.size() - 1;

            is_find = true;

            break;
          }
        }

        if (value_3 != vertexes_[runner].condition_) {
          if (value_3 == second) {
            vertexes_.emplace_back(Node(runner, value_3, vertexes_[runner].count_ + 1));
            pos = vertexes_.size() - 1;

            is_find = true;

            break;
          }
        }

        if (value_4 != vertexes_[runner].condition_) {
          if (value_4 == second) {
            vertexes_.emplace_back(Node(runner, value_4, vertexes_[runner].count_ + 1));
            pos = vertexes_.size() - 1;

            is_find = true;

            break;
          }
        }

        ++runner;
      }

      if (!is_find) {
        auto fix_size = static_cast<int>(vertexes_.size());

        while (node < fix_size) {
          value_1 = FirstOperation(vertexes_[node].condition_);
          value_2 = SecondOperation(vertexes_[node].condition_);
          value_3 = ThirdOperation(vertexes_[node].condition_);
          value_4 = FourthOperation(vertexes_[node].condition_);

          if (having_.find(value_1) == having_.end()) {
            vertexes_.emplace_back(Node(node, value_1, vertexes_[node].count_ + 1));

            having_.emplace(value_1);
          }
          if (having_.find(value_2) == having_.end()) {
            vertexes_.emplace_back(Node(node, value_2, vertexes_[node].count_ + 1));

            having_.emplace(value_2);
          }
          if (having_.find(value_3) == having_.end()) {
            vertexes_.emplace_back(Node(node, value_3, vertexes_[node].count_ + 1));

            having_.emplace(value_3);
          }
          if (having_.find(value_4) == having_.end()) {
            vertexes_.emplace_back(Node(node, value_4, vertexes_[node].count_ + 1));

            having_.emplace(value_4);
          }

          ++node;
        }
      }
    }

    PrintWay(pos);
  }
};

int main() {
  int first = 0;
  int second = 0;
  std::cin >> first >> second;

  Graph graph(first, second);

  return 0;
}