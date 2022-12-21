// Профессору Форду необходимо попасть на международную конференцию. Он хочет потратить на
// дорогу наименьшее количество денег, поэтому решил, что будет путешествовать исключительно
// ночными авиарейсами (чтобы не тратиться на ночевку в отелях), а днем будет осматривать
// достопримечательности тех городов, через которые он будет проезжать транзитом. Он
// внимательно изучил расписание авиаперелетов и составил набор подходящих авиарейсов,
// выяснив, что перелеты на выбранных направлениях совершаются каждую ночь и за одну ночь он
// не сможет совершить два перелета.

// Теперь профессор хочет найти путь наименьшей стоимости, учитывая что до конференции
// осталось K ночей (то есть профессор может совершить не более K перелетов).

// В первой строке находятся числа N (2 ≤ N ≤ 100) (количество городов), M (1 ≤ M ≤ 105)
// (количество авиарейсов), K (1 ≤ K ≤ 100) (количество оставшихся ночей), S (1 ≤ S ≤ N)
// (номер города, в котором живет профессор), F (1 ≤ F ≤ N) (номер города, в котором
// проводится конференция).

// Далее идет M строк, задающих расписание авиарейсов. i-я строка содержит три натуральных
// числа: Si, Fi и Pi, где Si — номер города, из которого вылетает i-й рейс, Fi — номер
// города, в который прилетает i-й рейс, Pi  — стоимость перелета i-м рейсом. Гарантируется,
// что 1 ≤ Si ≤ N, 1 ≤ Fi ≤ N, 1 ≤ Pi ≤ 106.

#include <iostream>
#include <unordered_map>
#include <vector>

class WeightedGraph {
 private:
  struct Edge {
    size_t begin_;
    size_t end_;
    size_t weight_;

    Edge(const size_t& beg, const size_t& end, const size_t& w) : begin_(beg), end_(end), weight_(w) {
    }
  };

  std::vector<Edge> edges_;
  size_t vertex_count_;
  size_t edges_count_;

  bool Relax(const Edge& edge, const std::vector<size_t>& dist, std::vector<size_t>& tmp_dist) {
    if ((dist[edge.begin_] != SIZE_MAX) && (dist[edge.end_] > dist[edge.begin_] + edge.weight_)) {
      tmp_dist[edge.end_] = dist[edge.begin_] + edge.weight_;

      return true;
    }

    return false;
  }

 public:
  WeightedGraph(const size_t& cities, const size_t& air_flights) : vertex_count_(cities), edges_count_(air_flights) {
    edges_.reserve(edges_count_);

    size_t begin = 0;
    size_t end = 0;
    size_t weight = 0;

    for (size_t i = 0; i < edges_count_; ++i) {
      std::cin >> begin >> end >> weight;
      --begin;
      --end;

      edges_.emplace_back(Edge(begin, end, weight));
    }
  }

  // using Bellman-Ford algorithm
  int GetExpense(const size_t& main_city, const size_t& required_city, const size_t& nights) {
    std::vector<size_t> dist(vertex_count_, SIZE_MAX);
    std::vector<size_t> tmp_dist(vertex_count_, SIZE_MAX);
    dist[main_city] = 0;
    tmp_dist[main_city] = 0;

    int count = 0;

    for (size_t i = 0; i < nights; ++i) {
      for (auto& edge : edges_) {
        if (Relax(edge, dist, tmp_dist)) {
          ++count;
        }
      }
      dist = tmp_dist;

      if (count == 0) {
        break;
      }
    }

    if (dist[required_city] == SIZE_MAX) {
      return -1;
    }

    return dist[required_city];
  }
};

int main() {
  size_t cities = 0;
  size_t air_flights = 0;
  size_t nights = 0;
  size_t main_city = 0;
  size_t required_city = 0;
  std::cin >> cities >> air_flights >> nights >> main_city >> required_city;
  --main_city;
  --required_city;

  WeightedGraph graph(cities, air_flights);

  std::cout << graph.GetExpense(main_city, required_city, nights) << "\n";

  return 0;
}