// Урбанист Варлам Ильинов каждый день катается на своем велосипеде по городу, оценивая
// качество велосипедных дорог, а также доступность его любимых кофеен. За годы своих трудов
// он смог составить подробную карту каждого района и выяснить за какое время он сможет
// добраться от одной кофейни до другой. Кроме того, если от одной кофейни до другой есть
// трамвайная линия, то он впадает в неистовый восторг и считает, что время на этом пути не
// тратится, а наоборот приобретается.

// Теперь он хочет измерить удобность транспортной инфраструктуры. Чем меньше максимальное
// расстояние между кофейнями, тем более удобным считается город. При этом, если от одной
// кофейни нельзя добраться до другой ни по велосипедным дорожкам, ни с помощью трамвая, то
// такая (упорядоченная) пара игнорируется при подсчете удобности.

// Необходимо найти пару кофеен, кратчайшее расстояние от одной из которых до другой
// максимально среди всех пар, между которыми есть какой-либо путь.

// В первой строке вводятся числа N и M (1 ≤ N ≤ 103, 1 ≤ M ≤ 5 ⋅ N) — количество кофеен и
// общее количество велосипедных дорожек и трамвайных путей. В следующих M строках задаются
// числа a, b, w, что означает наличие пути от кофейни a до кофейни b длины w ∈ [-100, 100]
// (но не наоборот!). Кофейни нумеруются с 0. Кольцевых трамвайных линий в городе не
// предусмотрено.

// Выведите искомое максимальное конечное кратчайшее расстояние между кофейнями.

#include <iostream>
#include <map>
#include <vector>

class WeightedGraph {
 private:
  struct Node {
    std::vector<std::pair<int64_t, int64_t> > transitions_;
  };

  std::vector<Node> vertexes_;
  int64_t size_;

  bool Relax(std::vector<int64_t>& dist, const int64_t& begin, const std::pair<int64_t, int64_t>& edge) {
    if ((dist[begin] != 10000000000000) && (dist[edge.second] > dist[begin] + edge.first)) {
      dist[edge.second] = dist[begin] + edge.first;

      return true;
    }

    return false;
  }

  // using Dijkstra algorithm
  int64_t GetMaxWay(const std::vector<int64_t>& potentials) {
    int64_t max = -10000000000000;

    for (int64_t v = 0; v < size_ - 1; ++v) {
      std::vector<bool> passed(size_ - 1, false);
      passed[v] = true;

      std::vector<int64_t> dist(size_ - 1, 10000000000000);
      dist[v] = 0;

      for (auto& edge : vertexes_[v].transitions_) {
        dist[edge.second] = edge.first;
      }

      std::multimap<int64_t, int64_t, std::less<int64_t> > map;
      for (int64_t i = 0; i < size_ - 1; ++i) {
        if (i != v) {
          map.emplace(dist[i], i);
        }
      }

      int64_t id_min = 0;
      int64_t weight = 0;

      while (!map.empty()) {
        id_min = map.begin()->second;
        weight = map.begin()->first;
        map.erase(map.begin());

        if (dist[id_min] != weight) {
          continue;
        }

        passed[id_min] = true;

        if ((weight != 10000000000000) && (weight - potentials[v] + potentials[id_min] > max)) {
          max = weight - potentials[v] + potentials[id_min];
        }

        for (auto& edge : vertexes_[id_min].transitions_) {
          if ((!passed[edge.second]) && (dist[edge.second] > dist[id_min] + edge.first)) {
            dist[edge.second] = dist[id_min] + edge.first;

            map.emplace(dist[edge.second], edge.second);
          }
        }
      }
    }

    return max;
  }

 public:
  WeightedGraph(const int64_t& n, const int64_t& m) : size_(n + 1) {
    vertexes_.resize(size_);

    int64_t begin = 0;
    int64_t end = 0;
    int64_t weight = 0;

    for (int64_t i = 0; i < m; ++i) {
      std::cin >> begin >> end >> weight;

      vertexes_[begin].transitions_.emplace_back(weight, end);
    }

    for (int64_t i = 0; i < size_ - 1; ++i) {
      vertexes_[size_ - 1].transitions_.emplace_back(0, i);
    }
  }

  // using Bellman-Ford algorithm
  std::vector<int64_t> GetPotentials(int64_t pos) {
    std::vector<int64_t> potentials(size_, 10000000000000);
    potentials[pos] = 0;

    int64_t count = 0;

    for (int64_t i = 0; i < size_ - 1; ++i) {
      count = 0;

      for (int64_t v = 0; v < size_; ++v) {
        for (auto& edge : vertexes_[v].transitions_) {
          if (Relax(potentials, v, edge)) {
            ++count;
          }
        }
      }

      if (count == 0) {
        break;
      }
    }

    return potentials;
  }

  int64_t GetDiameter() {
    auto potentials = GetPotentials(size_ - 1);

    for (int64_t i = 0; i < size_ - 1; ++i) {
      for (auto& edge : vertexes_[i].transitions_) {
        edge.first += potentials[i] - potentials[edge.second];
      }
    }

    return GetMaxWay(potentials);
  }
};

int main() {
  int64_t n = 0;
  int64_t m = 0;
  std::cin >> n >> m;

  WeightedGraph graph(n, m);

  std::cout << graph.GetDiameter() << "\n";

  return 0;
}