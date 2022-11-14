// Шел 2100-й год. Физтех стал огромным ВУЗом, состоящим из большого множества корпусов
// и гипертонеллей в качестве переходов между ними. Отныне до Тимирязевской (как и от
// любого другого корпуса) можно добраться за 5 минут от общежития (или любого другого
// здания университета) с помощью гиперлупов (напрямую или с пересадочными станциями в
// каждом корпусе).
// К сожалению, иногда переходы могут быть обесточены во время проведения ремонтных
// работ, а значит перемещаться по ним нельзя. Нужно выяснить, сколько гипертоннелей
// для гиперлупов надо построить, чтобы при неисправности любого из переходов физтех
// оставался связным.

// Учитывая то, что систему разрабатывали самые лучшие ученые страны, в ней нет
// бессмысленных кратных ребер и петель.

// ------------------------
// UNCOMPLETED
// ------------------------

#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

class Graph {
 public:
  enum Color { White, Gray, Black };

 private:
  struct Node {
    std::unordered_set<int> transitions_;
    int num_component_;
    int time_in_;
    int time_up_;

    Node() : time_in_(-1), time_up_(-1) {
    }
  };

  std::vector<Color> colors_;
  std::vector<Color> c_colors_;
  std::vector<Node> vertexes_;
  int size_;
  int time_;

 public:
  struct DoublyConnectedComponent {
    std::unordered_set<int> transitions_;
    int time_top_;

    DoublyConnectedComponent() : time_top_(-1) {
    }
  };

  Graph(const int& n, const int& m) : size_(n), time_(0) {
    vertexes_.resize(n);
    colors_.resize(n);

    int first = 0;
    int second = 0;

    for (int i = 0; i < m; ++i) {
      std::cin >> first >> second;
      --first;
      --second;

      vertexes_[first].transitions_.emplace(second);
      vertexes_[second].transitions_.emplace(first);
    }
  }

  void DfsVisit(const int& node, int from, std::vector<DoublyConnectedComponent>& components, int& count,
                std::vector<std::unordered_set<int> >& connections) {
    colors_[node] = Gray;
    vertexes_[node].num_component_ = count - 1;
    vertexes_[node].time_in_ = time_;
    vertexes_[node].time_up_ = time_++;
    components[count - 1].time_top_ = vertexes_[node].time_in_;

    c_colors_[vertexes_[node].num_component_] = Gray;

    std::cout << "to " << node + 1 << "\n";

    std::unordered_set<int> passed_neighbors;

    for (auto& neighbor : vertexes_[node].transitions_) {
      if ((colors_[neighbor] == Gray) && (neighbor != from)) {
        vertexes_[node].time_up_ = std::min(vertexes_[node].time_up_, vertexes_[neighbor].time_in_);
      } else if (colors_[neighbor] == White) {
        passed_neighbors.emplace(neighbor);

        DfsVisit(neighbor, node, components, count, connections);
        std::cout << "EDGE: " << node + 1 << " " << neighbor + 1 << "\n";

        vertexes_[node].num_component_ = count - 1;
        vertexes_[node].time_up_ = std::min(vertexes_[node].time_up_, vertexes_[neighbor].time_up_);

        std::cout << "check: " << node + 1 << " " << vertexes_[node].num_component_ + 1 << "\n";

        if (vertexes_[node].time_in_ < vertexes_[neighbor].time_up_) {
          components.emplace_back(DoublyConnectedComponent());
          connections.emplace_back(std::unordered_set<int>());
          c_colors_.emplace_back(Gray);
          ++count;

          components[count - 1].time_top_ = vertexes_[node].time_in_;
          components[vertexes_[node].num_component_].time_top_ = vertexes_[neighbor].time_in_;

          std::cout << "passed_neighbors: ";
          for (auto& next : passed_neighbors) {
            std::cout << next + 1 << " ";
          }
          std::cout << "| " << vertexes_[node].num_component_ + 1 << "\n";

          for (auto& compon : connections[vertexes_[node].num_component_]) {
            if (components[compon].time_top_ <= components[vertexes_[node].num_component_].time_top_) {
              components[compon].transitions_.erase(vertexes_[node].num_component_);
              components[vertexes_[node].num_component_].transitions_.erase(compon);

              if (c_colors_[compon] == Black) {
                components[compon].transitions_.emplace(count - 1);
                components[count - 1].transitions_.emplace(compon);

                connections[compon].emplace(count - 1);
                connections[count - 1].emplace(compon);
              }
            }
          }

          c_colors_[vertexes_[node].num_component_] = Black;
          vertexes_[node].num_component_ = count - 1;
        }
        for (auto& passed : passed_neighbors) {
          if ((vertexes_[node].num_component_ != vertexes_[passed].num_component_)) {
            components[vertexes_[passed].num_component_].transitions_.emplace(vertexes_[node].num_component_);
            connections[vertexes_[node].num_component_].emplace(vertexes_[passed].num_component_);

            components[vertexes_[node].num_component_].transitions_.emplace(vertexes_[passed].num_component_);
            connections[vertexes_[passed].num_component_].emplace(vertexes_[node].num_component_);
          }
        }
        std::cout << vertexes_[node].num_component_ + 1 << " " << vertexes_[neighbor].num_component_ + 1 << "\n";

        for (size_t i = 0; i < components.size(); ++i) {
          std::cout << i + 1 << ": ";
          for (auto& node : components[i].transitions_) {
            std::cout << node + 1 << " ";
          }
          std::cout << "\n";
        }
      }
    }

    colors_[node] = Black;
  }

  std::vector<DoublyConnectedComponent> GetDoublyConnectedComponents() {
    std::vector<DoublyConnectedComponent> components;
    components.reserve(10);

    std::vector<std::unordered_set<int> > connections;
    connections.reserve(10);

    c_colors_.reserve(10);

    int count = 1;
    components.emplace_back(DoublyConnectedComponent());
    connections.emplace_back(std::unordered_set<int>());
    c_colors_.emplace_back(White);

    for (int node = 0; node < size_; ++node) {
      if (colors_[node] == White) {
        DfsVisit(node, node, components, count, connections);
      }
    }

    return components;
  }
};

int GetPoints(const std::vector<Graph::DoublyConnectedComponent>& components, std::vector<Graph::Color> colors);
void DfsVisit(const std::vector<Graph::DoublyConnectedComponent>& components, std::vector<Graph::Color>& colors,
              const int& node, int& count);

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  Graph graph(n, m);

  auto components = std::move(graph.GetDoublyConnectedComponents());
  std::cout << "components\n";

  for (size_t i = 0; i < components.size(); ++i) {
    std::cout << i + 1 << ": ";
    for (auto& node : components[i].transitions_) {
      std::cout << node + 1 << " ";
    }
    std::cout << "\n";
  }

  if (components.size() != 1) {
    auto count = std::move(GetPoints(components, std::vector<Graph::Color>(components.size(), Graph::Color::White)));

    if (count % 2 == 0) {
      std::cout << count / 2 << "\n";
    } else {
      std::cout << count / 2 + 1 << "\n";
    }
  } else {
    std::cout << 0 << "\n";
  }

  return 0;
}

int GetPoints(const std::vector<Graph::DoublyConnectedComponent>& components, std::vector<Graph::Color> colors) {
  int count = 0;

  for (size_t node = 0; node < components.size(); ++node) {
    if (colors[node] == Graph::Color::White) {
      DfsVisit(components, colors, node, count);
    }
  }

  return count;
}

void DfsVisit(const std::vector<Graph::DoublyConnectedComponent>& components, std::vector<Graph::Color>& colors,
              const int& node, int& count) {
  colors[node] = Graph::Color::Gray;

  for (auto& neighbor : components[node].transitions_) {
    if (colors[neighbor] == Graph::Color::White) {
      DfsVisit(components, colors, neighbor, count);
    }
  }

  colors[node] = Graph::Color::Black;

  if (components[node].transitions_.size() == 1) {
    ++count;
  }
}