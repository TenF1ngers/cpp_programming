// Твоя наука — полная ерунда! Чего из-за неё волноваться? Если ты не откроешь 
// какую-нибудь молекулу, её обязательно откроет кто-то другой. А вот если с нервами 
// что-то случится, никто к тебе не придёт и не скажет: «Возьми, дружок, пучок моих 
// нервишек, а то, кажется, у меня лишние!»

// Смешарики открыли для себя 2D-строй — теперь построение будет не в одну шеренгу, а в
// прямоугольник. Для новой серии научно-популярного шоу смешарикам необходимо найти
// в творческой команде самого сообразительного смешарика, принявшего участие в
// наименьшем количестве выпусков. Командой может быть любой подпрямоугольник смешариков.
// Вам нужно помочь нашим героям для каждой команды, которую они попросят, найти самого
//редкого гостя на экране.

#include <iostream>
#include <vector>

class SparseTable2D {
 private:
 public:
  using Vector4D = std::vector<std::vector<std::vector<std::vector<int64_t> > > >;

  Vector4D sparse_table_2d;
  explicit SparseTable2D(const int& m, const int& n) {
    int pow_of_two_line = 32 - __builtin_clz(m) - 1;
    int pow_of_two_col = 32 - __builtin_clz(n) - 1;

    sparse_table_2d.resize(m, std::vector<std::vector<std::vector<int64_t> > >(
                                  pow_of_two_line + 1,
                                  std::vector<std::vector<int64_t> >(n, std::vector<int64_t>(pow_of_two_col + 1, 0))));

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        std::cin >> sparse_table_2d[i][0][j][0];
      }
    }

    int power_line = 0;
    int power_col = 0;

    for (int k_col = 1; k_col < pow_of_two_col + 1; ++k_col) {
      power_col = 1 << k_col;

      for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n - power_col + 1; ++j) {
          sparse_table_2d[i][0][j][k_col] =
              std::min(sparse_table_2d[i][0][j][k_col - 1],
                       sparse_table_2d[i][0][j + power_col - (1 << (k_col - 1))][k_col - 1]);
        }
      }
    }

    for (int k_line = 1; k_line < pow_of_two_line + 1; ++k_line) {
      power_line = (1 << k_line);

      for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m - power_line + 1; ++i) {
          sparse_table_2d[i][k_line][j][0] =
              std::min(sparse_table_2d[i][k_line - 1][j][0],
                       sparse_table_2d[i + power_line - (1 << (k_line - 1))][k_line - 1][j][0]);
        }
      }
    }

    for (int k_line = 1; k_line < pow_of_two_line + 1; ++k_line) {
      power_line = 1 << k_line;

      for (int k_col = 1; k_col < pow_of_two_col + 1; ++k_col) {
        power_col = 1 << k_col;

        for (int i = 0; i < m - power_line + 1; ++i) {
          for (int j = 0; j < n - power_col + 1; ++j) {
            sparse_table_2d[i][k_line][j][k_col] =
                std::min(std::min(sparse_table_2d[i][k_line - 1][j][k_col - 1],
                                  sparse_table_2d[i + power_line - (1 << (k_line - 1))][k_line - 1][j][k_col - 1]),
                         std::min(sparse_table_2d[i][k_line - 1][j + power_col - (1 << (k_col - 1))][k_col - 1],
                                  sparse_table_2d[i + power_line - (1 << (k_line - 1))][k_line - 1]
                                                 [j + power_col - (1 << (k_col - 1))][k_col - 1]));
          }
        }
      }
    }
  }

  [[nodiscard]] int64_t Query(const int& x1, const int& y1, const int& x2, const int& y2) const {
    int k_line = 32 - __builtin_clz(x2 - x1 + 1) - 1;
    int k_col = 32 - __builtin_clz(y2 - y1 + 1) - 1;

    return std::min(
        std::min(sparse_table_2d[x1][k_line][y1][k_col], sparse_table_2d[x2 + 1 - (1 << k_line)][k_line][y1][k_col]),
        std::min(sparse_table_2d[x1][k_line][y2 + 1 - (1 << k_col)][k_col],
                 sparse_table_2d[x2 + 1 - (1 << k_line)][k_line][y2 + 1 - (1 << k_col)][k_col]));
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int m = 0;
  int n = 0;
  std::cin >> m >> n;

  SparseTable2D st_2d(m, n);

  int q = 0;
  std::cin >> q;

  int x1 = 0;
  int y1 = 0;

  int x2 = 0;
  int y2 = 0;

  while (q != 0) {
    std::cin >> x1 >> y1 >> x2 >> y2;
    --x1;
    --y1;
    --x2;
    --y2;

    std::cout << st_2d.Query(x1, y1, x2, y2) << "\n";

    --q;
  }

  return 0;
}