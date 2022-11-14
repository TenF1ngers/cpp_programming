// На вход подается строка s (1≤∣s∣≤2⋅10^5), состоящая из строчных латинских букв.

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Node {
  public:

    char symbol_to_this;
    std::unordered_map<char, int> transitions;
    int parent;
    int suff_link;
    int length;

    Node() : symbol_to_this('#'), parent(-1), suff_link(-1), length(0) {
    }

    explicit Node(const char& symbol, const int& parent) : symbol_to_this(symbol), parent(parent), suff_link(-1), length(0) {
    }
};

class SuffixAutomaton {
  private:

    std::vector<Node> vertexes_;
    int id_last_;

    void AddSymbol(const char& symbol) {
      vertexes_.emplace_back(Node(symbol, id_last_));
      auto new_node = static_cast<int>(vertexes_.size() - 1);
      vertexes_[new_node].length = vertexes_[id_last_].length + 1;

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

    void Build(const std::string& main_str) {
      auto size_str = static_cast<int>(main_str.size());
      vertexes_.reserve(size_str + 1);

      for (int i = 0; i < size_str; ++i) {
        this->AddSymbol(main_str[i]);
      }
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

int main() {
  std::string main_str;
  std::cin >> main_str;

  SuffixAutomaton automaton;

  automaton.Build(main_str);

  automaton.Print();

  return 0;
}