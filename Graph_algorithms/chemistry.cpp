// Вася и Сережа играют в следующую игру. В некоторых клетках клетчатого листка Сережа рисует
// один из символов H, O, N или C, после чего Вася должен провести между некоторыми
// находящимися в соседних клетках символами линии так, чтобы получилось корректное
// изображение химической молекулы. К сожалению, Сережа любит рисовать много символов, и Вася
// не может сразу определить, возможно ли вообще нарисовать линии нужным способом. Помогите
// ему написать программу, которая даст ответ на этот вопрос.

// В этой задаче проведенные между символами химических элементов линии будем считать
// корректным изображением молекулы, если они удовлетворяют следующим условиям:

// каждая линия соединяет символы, нарисованные в соседних (по стороне) клетках;

// между каждой парой символов проведено не более одной линии;

// от каждого элемента отходит ровно столько линий, какова валентность этого элемента (1 для
// H, 2 для O, 3 для N, 4 для C);

// пустые клетки ни с чем не соединены;

// хотя бы в одной клетке нарисован какой-то символ.

// Первая строка входного файла содержит два натуральных числа n и m (1 ≤ n, m ≤ 50) — размеры
// листочка, на котором рисует Сережа. Далее следуют n строк по m символов в каждой, задающих
// конфигурацию химических элементов, которую нарисовал Сережа; пустые клетки задаются
// символом «.».

// В выходной файл выведите одно слово Valid, если линии провести требуемым образом можно,
// и Invalid, если нельзя.

#include <iostream>
#include <map>
#include <vector>

class System {
 private:
  enum Color { White, Gray, Black };

  std::map<char, int> valence_ = {{'.', 0}, {'H', 1}, {'O', 2}, {'N', 3}, {'C', 4}};

  std::vector<std::map<int, int, std::greater<int> > > vertexes_;
  std::vector<Color> colors_;

  int size_;
  int start_volume_;
  int finish_volume_;

  bool DfsVisit(const int& current, int& min_flow, const int& finish, std::vector<int>& key_v) {
    colors_[current] = Gray;

    for (auto& edge : vertexes_[current]) {
      if ((colors_[edge.first] == White) && (edge.second > 0)) {
        if (edge.second < min_flow) {
          min_flow = edge.second;
        }

        if (edge.first == finish) {
          edge.second -= min_flow;
          vertexes_[edge.first][current] += min_flow;

          colors_[current] = White;

          return true;
        }

        if (DfsVisit(edge.first, min_flow, finish, key_v)) {
          edge.second -= min_flow;
          vertexes_[edge.first][current] += min_flow;

          colors_[current] = White;

          return true;
        }
      }
    }

    colors_[current] = Black;
    key_v.emplace_back(current);

    return false;
  }

  int GetPos(const int& i, const int& j, const int& m) {
    return i * m + j + 1;
  }

 public:
  System(const int& n, const int& m) : size_(n * m + 2), start_volume_(0), finish_volume_(0) {
    vertexes_.resize(size_);
    colors_.resize(size_);

    char molecule;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::cin >> molecule;

        if ((i % 2 + j % 2) % 2 == 0) {
          vertexes_[0].emplace(GetPos(i, j, m), valence_[molecule]);
          start_volume_ += valence_[molecule];

          if (i + 1 < n) {
            vertexes_[GetPos(i, j, m)].emplace(GetPos(i + 1, j, m), 1);
          }

          if (i - 1 >= 0) {
            vertexes_[GetPos(i, j, m)].emplace(GetPos(i - 1, j, m), 1);
          }

          if (j + 1 < m) {
            vertexes_[GetPos(i, j, m)].emplace(GetPos(i, j + 1, m), 1);
          }

          if (j - 1 >= 0) {
            vertexes_[GetPos(i, j, m)].emplace(GetPos(i, j - 1, m), 1);
          }
        } else {
          vertexes_[GetPos(i, j, m)].emplace(size_ - 1, valence_[molecule]);
          finish_volume_ += valence_[molecule];
        }
      }
    }
  }

  // using Ford-Fulkerson algorithm
  bool Executable() {
    int min_flow = 5;
    int max = 0;

    std::vector<int> key_v;

    while (DfsVisit(0, min_flow, size_ - 1, key_v)) {
      max += min_flow;

      for (size_t i = 0; i < key_v.size(); ++i) {
        colors_[key_v[i]] = White;
      }
      key_v.resize(0);

      min_flow = 5;
    }

    return (max == start_volume_) && (max == finish_volume_) && (max != 0);
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  System graph(n, m);

  if (graph.Executable()) {
    std::cout << "Valid\n";
  } else {
    std::cout << "Invalid\n";
  }

  return 0;
}