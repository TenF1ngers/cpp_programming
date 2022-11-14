// Итак — постройте суффиксное дерево для заданной строки s.

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

    void Build(const std::string& main_str) {
      auto size_str = static_cast<int>(main_str.size());
      vertexes_.reserve(size_str + 1);

      for (int i = size_str - 1; i >= 0; --i) {
        this->AddSymbol(main_str[i]);
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

    SuffixTree(SuffixAutomaton& automaton, const std::string& str) : main_str(str) {

      auto vert_size = static_cast<int>(automaton.vertexes_.size());
      auto str_size = static_cast<int>(main_str.size());
      vertexes.resize(vert_size);

      vertexes[0].begin = -1;
      vertexes[0].length = 0;

      int suff = 0;

      for (int i = 1; i < vert_size; ++i) {
        suff = automaton.vertexes_[i].suff_link;

        vertexes[i].begin = str_size - (automaton.vertexes_[i].end_pos - automaton.vertexes_[suff].length);
        vertexes[i].length = automaton.vertexes_[i].length - automaton.vertexes_[suff].length;
        vertexes[suff].transitions[main_str[vertexes[i].begin]] = i;
      }
    }

    void PrintSuffixTree() {
      std::cout << vertexes.size() << "\n";

      for (int i = 0; i < static_cast<int>(vertexes.size()); ++i) {
        for (auto j : vertexes[i].transitions) {
          std::cout << i << " " << j.first << " " << vertexes[j.second].length << " " << j.second << "\n";
        }
      }
    }
};

int main() {
  std::string main_str;
  std::cin >> main_str;
  main_str.push_back('#');

  SuffixAutomaton automaton;

  automaton.Build(main_str);

  SuffixTree suff_tree(automaton, main_str);

  suff_tree.PrintSuffixTree();

  return 0;
}