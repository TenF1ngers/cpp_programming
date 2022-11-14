// Реализуйте структуру «множество строк», поддерживающие добавление (+) и поиск (?) элементов
// в множестве.

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class Node {
 public:
  bool is_term;
  std::unordered_map<char, int> children;

  Node() : is_term(false) {
  }
};

class Trie {
 public:
  std::vector<Node> vertexes;

  Trie() {
    vertexes.resize(1);
  }

  void Push(const std::string& str) {
    int pos = 0;

    for (int j = 0; j < static_cast<int>(str.size()); ++j) {
      if (vertexes[pos].children.find(str[j]) == vertexes[pos].children.end()) {
        vertexes.emplace_back(Node());
        vertexes[pos].children[str[j]] = static_cast<int>(vertexes.size()) - 1;
      }

      pos = vertexes[pos].children[str[j]];
    }

    vertexes[pos].is_term = true;
  }

  bool Contains(const std::string& str) {
    int pos = 0;

    for (int j = 0; j < static_cast<int>(str.size()); ++j) {
      if (vertexes[pos].children.find(str[j]) == vertexes[pos].children.end()) {
        return false;
      }

      pos = vertexes[pos].children[str[j]];
    }

    return vertexes[pos].is_term;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  char symbol = '.';
  std::cin >> symbol;

  std::string str;

  Trie trie;

  while (symbol != '#') {
    switch (symbol) {
      case '+': {
        std::cin >> str;

        trie.Push(str);

        break;
      }
      case '?': {
        std::cin >> str;

        if (trie.Contains(str)) {
          std::cout << "YES\n";
        } else {
          std::cout << "NO\n";
        }

        break;
      }
    }

    std::cin >> symbol;
  }

  return 0;
}