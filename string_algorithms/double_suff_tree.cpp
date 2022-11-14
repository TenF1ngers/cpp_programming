#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class SuffixAutomaton {
  public:
    class Node {
    public:

      char symbol_to_this;
      std::unordered_map<char, int> transitions;
      int parent;
      int suff_link;
      int length;
      int end_pos;

      Node() : symbol_to_this('#'), parent(-1), suff_link(-1), length(0), end_pos(0) {
      }

      explicit Node(const char& symbol, const int& parent) : symbol_to_this(symbol), parent(parent), suff_link(-1), length(0) {
      }
    };

    std::vector<Node> vertexes_;
    int id_last_;
    int first_size;
    int second_size;

  private:

    void AddSymbol(const char& symbol) {
      vertexes_.emplace_back(Node(symbol, id_last_));
      auto new_node = static_cast<int>(vertexes_.size() - 1);
      vertexes_[new_node].length = vertexes_[id_last_].length + 1;
      vertexes_[new_node].end_pos = vertexes_[id_last_].end_pos + 1;

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

    int Clone(const char& symbol, const int& check_symbol, int parent) {
      vertexes_.emplace_back(Node(symbol, parent));
      auto clone = static_cast<int>(vertexes_.size() - 1);

      vertexes_[clone].end_pos = vertexes_[check_symbol].end_pos;
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

  public:

    void Build(const std::string& main_str, int& fir_size, int& sec_size) {
      vertexes_.reserve(fir_size + sec_size);

      for (int i = fir_size + sec_size - 1; i >= fir_size; --i) {
        this->AddSymbol(main_str[i]);
      }

      second_size = static_cast<int>(vertexes_.size());

      for (int i = fir_size - 1; i >= 0; --i) {
        this->AddSymbol(main_str[i]);
      }

      first_size = static_cast<int>(vertexes_.size()) - second_size;
    }

    void Print() {
      auto size = static_cast<int>(vertexes_.size());
      for (int i = 0; i < size; ++i) {
        std::cout << vertexes_[i].suff_link << " ";
      }

      std::cout << "\n" << size << "\n";

      for (int i = 0; i < size; ++i) {
        for (int j = 'a'; j < 'z' + 1; ++j) {
          if (vertexes_[i].transitions.find(j) != vertexes_[i].transitions.end()) {
            std::cout << i << " " << static_cast<char>(j) << " " << vertexes_[i].transitions[j] << "\n";
          }
        }
      }
    }

    SuffixAutomaton() : id_last_(0) {
      vertexes_.resize(1);
    }
};

class SuffixTree {
  public:

    class Node {
      public:
        std::unordered_map<char, int> transitions;
        int begin;
        int length;
    };

    std::vector<Node> vertexes;
    std::string main_str;

    SuffixTree(SuffixAutomaton& automaton, const std::string& str, const int& fir_size, const int& sec_size) : main_str(str) {
      vertexes.resize(automaton.vertexes_.size());

      vertexes[0].begin = -1;
      vertexes[0].length = 0;

      int suff = 0;

      for (int i = 1; i < automaton.second_size; ++i) {
        suff = automaton.vertexes_[i].suff_link;

        vertexes[i].begin = sec_size + fir_size - (automaton.vertexes_[i].end_pos - automaton.vertexes_[suff].length);
        vertexes[i].length = automaton.vertexes_[i].length - automaton.vertexes_[suff].length;
        vertexes[suff].transitions[main_str[vertexes[i].begin]] = i;
      }

      for (int i = automaton.second_size; i < static_cast<int>(automaton.vertexes_.size()); ++i) {
        suff = automaton.vertexes_[i].suff_link;

        vertexes[i].begin = fir_size + sec_size - (automaton.vertexes_[i].end_pos - automaton.vertexes_[suff].length);
        vertexes[i].length = automaton.vertexes_[i].length - automaton.vertexes_[suff].length;
        vertexes[suff].transitions[main_str[vertexes[i].begin]] = i;
      }
    }

    void PrintSuffixTree() {
      std::cout << vertexes.size() << "\n";

      auto dollar = static_cast<int32_t>(main_str.find('$'));

      for (size_t i = 0; i < vertexes.size(); i++) {
        for (auto j : vertexes[i].transitions) {
          int id = vertexes[j.second].begin;

          if (id <= dollar && dollar <= id + static_cast<int>(vertexes[j.second].length) - 1) {
            vertexes[j.second].transitions.clear();
            std::cout << i << " " << j.first<< " " << dollar - id + 1 << " " << j.second << '\n';
          } else {
            std::cout << i << " " << j.first<< " " << vertexes[j.second].length << " " << j.second << '\n';
          }
        }
      }
    }
};

int main() {
  std::string first;
  std::string second;
  std::cin >> first >> second;
  
  auto fir_size = static_cast<int>(first.size());
  auto sec_size = static_cast<int>(second.size());

  first += second;

  SuffixAutomaton automaton;
  automaton.Build(first, fir_size, sec_size);

  SuffixTree suff_tree(automaton, first, fir_size, sec_size);
  suff_tree.PrintSuffixTree();

  return 0;
}