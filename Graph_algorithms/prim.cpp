// Требуется найти в связном графе остовное дерево минимального веса. Задачу решайте с
// помощью алгоритма Прима

#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

class WeightedGraph {
 private:
  struct Node {
    std::multimap<int, int, std::less<int> > transitions_; // <weight, end>
  };

  std::vector<Node> vertexes_;
  int size_;

 public:
  WeightedGraph(const int& n, const int& m) : size_(n) {
    vertexes_.resize(n);

    int begin = 0;
    int end = 0;
    int weight = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> begin >> end >> weight;
      --begin;
      --end;

      vertexes_[begin].transitions_.emplace(weight, end);
      vertexes_[end].transitions_.emplace(weight, begin);
    }
  }

  // using Prim algorithm
  int64_t GetMinSpanningTreeWeight() {
    int64_t sum = 0;

    std::multimap<int, std::pair<int, int>, std::less<int> > collection; // <weight, <begin, end> >

    collection.emplace(vertexes_[0].transitions_.begin()->first,
                       std::pair<int, int>(0, vertexes_[0].transitions_.begin()->second));

    std::unordered_set<int> availability;
    availability.emplace(0);

    int begin = 0;
    int end = 0;
    int weight = 0;

    while (static_cast<int>(availability.size()) != size_) {
      begin = collection.begin()->second.first;
      end = collection.begin()->second.second;
      weight = collection.begin()->first;

      if (availability.find(end) == availability.end()) {
        sum += weight;
      }

      availability.emplace(end);
      collection.extract(collection.begin());

      for (auto neighbor = vertexes_[begin].transitions_.begin(); neighbor != vertexes_[begin].transitions_.end();
           ++neighbor) {
        if (availability.find(neighbor->second) == availability.end()) {
          collection.emplace(neighbor->first, std::pair<int, int>(begin, neighbor->second));

          break;
        }
      }

      for (auto neighbor = vertexes_[end].transitions_.begin(); neighbor != vertexes_[end].transitions_.end();
           ++neighbor) {
        if (availability.find(neighbor->second) == availability.end()) {
          collection.emplace(neighbor->first, std::pair<int, int>(end, neighbor->second));

          break;
        }
      }
    }

    return sum;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  WeightedGraph graph(n, m);

  std::cout << graph.GetMinSpanningTreeWeight() << "\n";

  return 0;
}