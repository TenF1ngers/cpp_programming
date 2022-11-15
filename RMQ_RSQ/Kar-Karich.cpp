// Можно всю жизнь прождать подходящий момент и в итоге так и не сказать друг другу
// что-то важное.

// Кто-то за ночь уничтожил выставку ледяных скульптур. Известно, что ни одному из
// смешариков в одиночку не хватило бы времени на такое. Налицо тайный сговор или 
//действия организованной преступной группировки. Смешарики решают провести суд
// Кар-Карычей — самый гуманный суд в мире. Всех смешариков построили в шеренгу, чтобы 
//выявить самую подозрительную группировку.

// Кар-Карыч считает, что группировкой может быть любой подотрезок из шеренги смешариков
// (общеизвестно, что все налетчики стараются держаться рядом). Также Кар-Карыч верит
// в то, что самая подозрительная группировка — группировка, у смешариков которой
// наибольшая суммарная подозрительность.

// Помогите Кар-Карычу и напишите программу, которая найдет самую подозрительную 
// группировку.

#include <iostream>

int main() {
  int n = 0;
  std::cin >> n;

  int left = 0;
  int right = 0;
  int last_zero_pos = 0;

  int64_t cur_sum = 0;
  int64_t max_sum = 0;

  int suspicion = 0;
  std::cin >> suspicion;

  max_sum = suspicion;

  for (int i = 1; i < n + 1; ++i) {
    cur_sum += suspicion;

    if (cur_sum >= max_sum) {
      max_sum = cur_sum;
      left = last_zero_pos + 1;
      right = i;
    }

    if (cur_sum < 0) {
      cur_sum = 0;
      last_zero_pos = i;
    }

    if (i != n) {
      std::cin >> suspicion;
    }
  }

  std::cout << left << " " << right << " " << max_sum;
  return 0;
}