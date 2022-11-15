// Я в детстве тоже хотела иметь волшебную палочку, чтобы сразу стать старенькой, как
// моя бабушка, получать пенсию и ничего не делать. Хорошо, что у меня не было волшебной 
//палочки.

// Смешарики устали сжигать калории на диете тревог и забот, поэтому сегодня происходит
// торжественное открытие Спартакиады. Совунье выпала честь наградить всех участников
// соревнований памятными наградами. Смешарики снова стоят в один ряд, а спортивной
// командой Совунья называет любой подотрезок этого ряда. Изначально у всех смешариков
// ноль наград, так что ваша задача — помочь провести награждение максимально быстро.
// Для этого Совунья сообщила вам, что смешариков всегда n=2^24.

// Собственно, награждение устроено достаточно просто, Совунья называет спортивную
// команду и количество наград, которое надо начислить смешарикам в команде. Всего таких
// «стадий награждения» будет m.

// Совунья хочет знать, не потратит ли она так все имеющиеся медали, а поэтому просит
// вас определить, сколько будет наград у команд после церемонии награждения. Таких
// запросов будет q.

#include <cmath>
#include <iostream>

unsigned int NextRand(unsigned int& cur, const unsigned int& a, const unsigned int& b) {
  cur = cur * a + b;
  return cur >> 8;
}

void Swap(unsigned int& first, unsigned int& second) {
  unsigned int tmp = first;
  first = second;
  second = tmp;
}

int main() {
  unsigned int m, q, a, b, cur = 0;
  std::cin >> m >> q >> a >> b;

  unsigned int len = 1 << 24;

  auto array = new unsigned int[len];
  for (int i = 0; i < len; ++i) {
    array[i] = 0;
  }

  unsigned int add, left, right;

  for (unsigned int i = 0; i < m; ++i) {
    add = NextRand(cur, a, b);
    left = NextRand(cur, a, b);
    right = NextRand(cur, a, b);
    if (left > right) {
      Swap(left, right);
    }
    array[left] += add;
    array[right + 1] -= add;
  }

  auto prefix = new int64_t[len];
  for (int i = 0; i < len; ++i) {
    prefix[i] = 0;
  }

  int64_t sum = array[0];
  prefix[0] = sum;

  for (unsigned int i = 1; i < len; ++i) {
    sum += array[i];
    prefix[i] = prefix[i - 1] + sum;
  }

  unsigned result = 0;

  for (unsigned int i = 0; i < q; ++i) {
    left = NextRand(cur, a, b);
    right = NextRand(cur, a, b);

    if (left > right) {
      Swap(left, right);
    }

    if (left == 0) {
      result += prefix[right];
    } else {
      result += prefix[right] - prefix[left - 1];
    }
  }

  std::cout << result << "\n";

  return 0;
}