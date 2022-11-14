// Уно, дос, кватро, поехали! Ослу и Коту в сапогах нужно держать ритм песни, а значит,
// прежде всего, следует определить ее рефрен (так называется определённый музыкальный
// материал, неоднократно повторяющийся на протяжении произведения, например, припев в
// песнях).В общих чертах методика поиска рефрена интуитивна — рассматривается
// последовательность n целых чисел от 1 до m. Подпоследовательность подряд идущих чисел
// называется рефреном, если произведение её длины на количество вхождений в
// последовательность максимально.

// От вас требуется две вещи:

// 1) По заданной последовательности найти её рефрен.

// 2) Оценить дуэт Осла и Кота в сапогах в примечании.

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class Node {
  public:

    int symbol_to_this;
    std::unordered_map<int, int> transitions;
    int parent;
    int suff_link;
    int length;
    bool is_clone;

    Node() : symbol_to_this(-1), parent(-1), suff_link(-1), length(0) {
    }

    explicit Node(const int& symbol, const int& parent) : symbol_to_this(symbol), parent(parent), suff_link(-1), length(0) {
    }
};

class SuffixAutomaton {
  private:

    std::vector<Node> vertexes_;
    std::multimap<int64_t, int, std::greater<int> > conditions_;
    std::vector<int64_t> cnt_endpos_;
    int id_last_;

    void AddSymbol(const int& symbol) {
      vertexes_.emplace_back(Node(symbol, id_last_));
      auto new_node = static_cast<int>(vertexes_.size() - 1);
      vertexes_[new_node].length = vertexes_[id_last_].length + 1;
      vertexes_[new_node].is_clone = false;

      vertexes_[id_last_].transitions[symbol] = new_node;
      id_last_ = vertexes_[id_last_].suff_link;

      while ((id_last_ != -1) && (vertexes_[id_last_].transitions.find(symbol) == vertexes_[id_last_].transitions.end())) {
        vertexes_[id_last_].transitions[symbol] = new_node;

        id_last_ = vertexes_[id_last_].suff_link;
      }

      if (id_last_ == -1) {
        vertexes_[new_node].suff_link = 0;
      } else {
        auto check_symbol = vertexes_[id_last_].transitions[symbol];

        if (vertexes_[check_symbol].length == vertexes_[id_last_].length + 1) {
          vertexes_[new_node].suff_link = check_symbol;
        } else {
          vertexes_[new_node].suff_link = Clone(symbol, check_symbol, id_last_);
        }
      }

      id_last_ = new_node;
    }

    int Clone(const int& symbol, const int& check_symbol, int parent) {
      vertexes_.emplace_back(Node(symbol, parent));
      auto clone = static_cast<int>(vertexes_.size() - 1);
      vertexes_[clone].is_clone = true;

      vertexes_[clone].transitions = vertexes_[check_symbol].transitions;
      vertexes_[clone].length = vertexes_[parent].length + 1;
      vertexes_[clone].suff_link = vertexes_[check_symbol].suff_link;
      vertexes_[check_symbol].suff_link = clone;

      while ((parent != -1) && (vertexes_[parent].transitions.find(symbol) != vertexes_[parent].transitions.end()) && (vertexes_[parent].transitions[symbol] == check_symbol)) {
        vertexes_[parent].transitions[symbol] = clone;

        parent = vertexes_[parent].suff_link;
      }

      return clone;
    }

    int64_t Composition(const int64_t& length, const int64_t& occurrence) {
      return length * occurrence;
    }

  public:

    void Build(const std::vector<int>& values) {
      auto size_arr = static_cast<int>(values.size());
      vertexes_.reserve(size_arr + 1);

      for (int i = 0; i < size_arr; ++i) {
        this->AddSymbol(values[i]);
      }

      cnt_endpos_.resize(vertexes_.size(), 0);

      for (int i = 1; i < static_cast<int>(vertexes_.size()); ++i) {
        if (!vertexes_[i].is_clone) {
          cnt_endpos_[i] = 1;
        } else {
          cnt_endpos_[i] = 0;
        }

        conditions_.insert(std::pair{vertexes_[i].length, i});
      }

      for (auto ptr = conditions_.begin(); ptr != conditions_.end(); ++ptr) {
        cnt_endpos_[vertexes_[ptr->second].suff_link] += cnt_endpos_[ptr->second];
      }
    }

    void Refrain() {
      int max_id = 0;

      for (int i = 1; i < static_cast<int>(vertexes_.size()); ++i) {
        if (Composition(vertexes_[max_id].length, cnt_endpos_[max_id]) < Composition(vertexes_[i].length, cnt_endpos_[i])) {
          max_id = i;
        }
      }

      std::cout << Composition(vertexes_[max_id].length, cnt_endpos_[max_id]) << "\n";
      std::cout << vertexes_[max_id].length << "\n";

      std::vector<int> refrain;
      refrain.resize(vertexes_[max_id].length, 0);

      int runner = max_id;
      for (int i = 0; i < vertexes_[max_id].length; ++i) {
        refrain[vertexes_[max_id].length - 1 - i] = vertexes_[runner].symbol_to_this;

        runner = vertexes_[runner].parent;
      }

      std::cout << refrain[0];

      for (int i = 1; i < vertexes_[max_id].length; ++i) {
        std::cout << " " << refrain[i];
      }
      std::cout << "\n";
    }

    SuffixAutomaton() : id_last_(0) {
      vertexes_.resize(1);
    }
};

int main() {
  std::vector<int> values;
  int n = 0;
  int m = 0;
  int value = 0;

  std::cin >> n >> m;
  values.reserve(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> value;

    values.emplace_back(value);
  }

  SuffixAutomaton automaton;
  automaton.Build(values);

  automaton.Refrain();

  return 0;
}