// Полный ориентированный взвешенный граф задан матрицей смежности. Постройте матрицу
// кратчайших путей между его вершинами. Гарантируется, что в графе нет циклов отрицательного
// веса.

// В первой строке вводится единственное число N (1 ≤ N ≤ 100) — количество вершин графа. В
// следующих N строках по N чисел задается матрица смежности графа (j-е число в i-й строке
// соответствует весу ребра из вершины i в вершину j). Все числа по модулю не превышают 100.
// На главной диагонали матрицы всегда нули.

// Выведите N строк по N чисел — матрицу кратчайших расстояний между парами вершин. j-е число
// в i-й строке должно быть равно весу кратчайшего пути из вершины i в вершину j.

#include <iostream>
#include <vector>

class WeightedGraph {
 private:
  std::vector<std::vector<int> > adjacency_;
  int size_;

 public:
  explicit WeightedGraph(const int& n) : size_(n) {
    adjacency_.resize(size_, std::vector<int>(size_));

    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        std::cin >> adjacency_[i][j];
      }
    }
  }

  // using Floyd-Warshall algorithm
  void GetShortestPathsMatrix() {
    for (int k = 0; k < size_; ++k) {
      for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j) {
          adjacency_[i][j] = std::min(adjacency_[i][j], adjacency_[i][k] + adjacency_[k][j]);
        }
      }
    }

    for (int i = 0; i < size_; ++i) {
      for (int j = 0; j < size_; ++j) {
        std::cout << adjacency_[i][j] << " ";
      }
      std::cout << "\n";
    }
  }
};

int main() {
  int n = 0;
  std::cin >> n;

  WeightedGraph graph(n);

  graph.GetShortestPathsMatrix();

  return 0;
}