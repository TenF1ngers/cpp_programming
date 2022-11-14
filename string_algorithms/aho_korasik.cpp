// В стандартном потоке ввода программе подаётся строка, состоящая из строчных латинских
// букв, которую мы назовём исходной. На следующей строке программе подаётся число N
// (1 ≤ N ≤ 1,000,000), а в следующих N строках — по уникальному слову из строчных латинских
// букв; эти слова мы назовём словарём. Суммарная длина слов из словая не превосходит 1,000,000

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>

class Node {
 public:
  bool is_term;
  std::string word;
  char symbol;
  int suff_link;
  int exit_link;
  int parent;
  std::unordered_map<char, int> children;

  Node() : is_term(false), symbol('.'), suff_link(-1), exit_link(-1) {
  }
};

class Trie {
 public:
  std::vector<Node> vertexes;

  Trie() {
    vertexes.resize(1);
  }

  void BuildSuffixLink() {
    std::queue<int> queue;

    for (int i = 'a'; i < 'z' + 1; ++i) {
        if (vertexes[0].children.find(i) != vertexes[0].children.end()) {
          vertexes[vertexes[0].children[i]].suff_link = 0;
          for (int j = 'a'; j < 'z' + 1; ++j) {
            if (vertexes[vertexes[0].children[i]].children.find(j) != vertexes[vertexes[0].children[i]].children.end()) {
              queue.push(vertexes[vertexes[0].children[i]].children[j]);
            }
          }
        }
    }

    std::pair<int, char> node;
    int suff = 0;

    while (!queue.empty()) {
      node.first = queue.front();
      node.second = vertexes[node.first].symbol;

      suff = vertexes[vertexes[node.first].parent].suff_link;

      while ((suff != -1) && (vertexes[suff].children.find(node.second) == vertexes[suff].children.end())) {
        suff = vertexes[suff].suff_link;
      }

      if (suff == -1) {
        if (vertexes[0].children.find(node.second) != vertexes[0].children.end()) {
          vertexes[node.first].suff_link = vertexes[0].children[node.second];
        } else {
          vertexes[node.first].suff_link = 0;
        }
      } else {
        vertexes[node.first].suff_link = vertexes[suff].children[node.second];
      }

      queue.pop();
      for (int i = 'a'; i < 'z' + 1; ++i) {
        if (vertexes[node.first].children.find(i) != vertexes[node.first].children.end()) {
          queue.push(vertexes[node.first].children[i]);
        }
      }
    }
  }

  void BuildExitLinks() {
    std::queue<int> queue;

    for (int i = 'a'; i < 'z' + 1; ++i) {
        if (vertexes[0].children.find(i) != vertexes[0].children.end()) {
          vertexes[vertexes[0].children[i]].exit_link = -1;
          for (int j = 'a'; j < 'z' + 1; ++j) {
            if (vertexes[vertexes[0].children[i]].children.find(j) != vertexes[vertexes[0].children[i]].children.end()) {
              queue.push(vertexes[vertexes[0].children[i]].children[j]);
            }
          }
        }
    }

    std::pair<int, char> node;
    int suff = 0;

    while (!queue.empty()) {
      node.first = queue.front();
      node.second = vertexes[node.first].symbol;

      suff = vertexes[node.first].suff_link;

      while ((suff != -1) && (!vertexes[suff].is_term)) {
        suff = vertexes[suff].suff_link;
      }

      vertexes[node.first].exit_link = suff;

      queue.pop();
      for (int i = 'a'; i < 'z' + 1; ++i) {
        if (vertexes[node.first].children.find(i) != vertexes[node.first].children.end()) {
          queue.push(vertexes[node.first].children[i]);
        }
      }
    }
  }

  void Push(const std::string& str) {
    int pos = 0;

    for (int j = 0; j < static_cast<int>(str.size()); ++j) {
      if (vertexes[pos].children.find(str[j]) == vertexes[pos].children.end()) {
        vertexes.emplace_back(Node());
        vertexes[pos].children[str[j]] = static_cast<int>(vertexes.size()) - 1;
        vertexes[vertexes.size() - 1].symbol = str[j];
        vertexes[vertexes.size() - 1].parent = pos;
      }

      pos = vertexes[pos].children[str[j]];
    }

    vertexes[pos].is_term = true;
    vertexes[pos].word = str;
  }
};

void AhoKorasik(Trie& trie, const std::string& main_str, std::unordered_map<std::string, int>& id_words, std::vector<std::pair<int, std::vector<int> > >& answer);
int NextState(Trie& trie, int pos, char& symbol);
void FindEntries(Trie& trie, int pos, int i, std::unordered_map<std::string, int>& id_words, std::vector<std::pair<int, std::vector<int> > >& answer);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string main_str;
  std::cin >> main_str;

  int n = 0;
  std::cin >> n;

  std::string tmp_str;

  Trie trie;

  std::unordered_map<std::string, int> id_words;
  std::vector<std::pair<int, std::vector<int> > > answer;
  answer.resize(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> tmp_str;
    id_words[tmp_str] = i;

    trie.Push(tmp_str);
  }

  trie.BuildSuffixLink();
  trie.BuildExitLinks();

  AhoKorasik(trie, main_str, id_words, answer);

  for (int i = 0; i < n; ++i) {
    if (answer[i].first == 0) {
      std::cout << 0 << "\n";
    } else {
      std::cout << answer[i].first << " ";

      for (auto j = answer[i].second.begin(); j < answer[i].second.end(); ++j) {
        std::cout << *j << " ";
      }

      std::cout << "\n";
    }
  }

  return 0;
}

void AhoKorasik(Trie& trie, const std::string& main_str, std::unordered_map<std::string, int>& id_words, std::vector<std::pair<int, std::vector<int> > >& answer) {
  int size = static_cast<int>(main_str.size());
  char symbol = '#';
  int pos = 0;

  for (int i = 0; i < size; ++i) {
    symbol = main_str[i];

    pos = NextState(trie, pos, symbol);
    FindEntries(trie, pos, i, id_words, answer);
  }
}

void FindEntries(Trie& trie, int pos, int i, std::unordered_map<std::string, int>& id_words, std::vector<std::pair<int, std::vector<int> > >& answer) {
  if (!trie.vertexes[pos].is_term) {
    pos = trie.vertexes[pos].exit_link;
  }

  int id = 0;

  while (pos != -1) {
    id = id_words[trie.vertexes[pos].word];
    ++answer[id].first;
    answer[id].second.emplace_back(i - trie.vertexes[pos].word.size() + 2);

    pos = trie.vertexes[pos].exit_link;
  }
}

int NextState(Trie& trie, int pos, char& symbol) {
  while ((pos != -1) && (trie.vertexes[pos].children.find(symbol) == trie.vertexes[pos].children.end())) {
    pos = trie.vertexes[pos].suff_link;
  }

  return (pos == -1 ? 0 : trie.vertexes[pos].children[symbol]);
}