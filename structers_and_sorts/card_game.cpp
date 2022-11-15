// В игре в зожника карточная колода раздается поровну двум игрокам. Далее они
// вскрывают по одной верхней карте, и тот, чья карта старше, забирает себе обе вскрытые
// карты, которые кладутся под низ его колоды. Тот, кто остается без карт — проигрывает.

// Для простоты будем считать, что все карты различны по номиналу, а также, что самая
// младшая карта побеждает самую старшую карту («шестерка берет туза»).

// Игрок, который забирает себе карты, сначала кладет под низ своей колоды карту первого
// игрока, затем карту второго игрока (то есть карта второго игрока оказывается внизу
// колоды).

// Напишите программу, которая моделирует игру в зожника и определяет, кто выигрывает.
// В игре участвует 10 карт, имеющих значения от 0 до 9, большая карта побеждает меньшую,
// карта со значением 0 побеждает карту 9.

#include <iostream>

struct Node {
  int val;
  Node* next;
  Node* pre;
};

struct Deck {
  Node* top;
  Node* bottom;
  size_t size;
};

void push_bottom(Deck& player, int val);
void pop_top(Deck& player);
void clear(Deck& player);

int main() {
  Deck player_1{nullptr, nullptr, 0};
  Deck player_2{nullptr, nullptr, 0};
  int val = 0;
  for (int i = 0; i < 5; ++i) {
    std::cin >> val;
    push_bottom(player_1, val);
  }
  for (int i = 0; i < 5; ++i) {
    std::cin >> val;
    push_bottom(player_2, val);
  }
  int countOfMoves = 0;
  while ((player_1.size != 0) && (player_2.size != 0)) {
    if ((player_1.top->val == 9) && (player_2.top->val == 0)) {
      push_bottom(player_2, player_1.top->val);
      push_bottom(player_2, player_2.top->val);
      pop_top(player_1);
      pop_top(player_2);
      ++countOfMoves;
    } else if ((player_1.top->val == 0) && (player_2.top->val == 9)) {
      push_bottom(player_1, player_1.top->val);
      push_bottom(player_1, player_2.top->val);
      pop_top(player_1);
      pop_top(player_2);
      ++countOfMoves;
    } else if (player_1.top->val > player_2.top->val) {
      push_bottom(player_1, player_1.top->val);
      push_bottom(player_1, player_2.top->val);
      pop_top(player_1);
      pop_top(player_2);
      ++countOfMoves;
    } else {
      push_bottom(player_2, player_1.top->val);
      push_bottom(player_2, player_2.top->val);
      pop_top(player_1);
      pop_top(player_2);
      ++countOfMoves;
    }
    if (countOfMoves == 1000000) {
      std::cout << "botva"
                << "\n";
      break;
    }
  }
  if (player_1.size == 0) {
    std::cout << "second " << countOfMoves << "\n";
  } else if (player_2.size == 0) {
    std::cout << "first " << countOfMoves << "\n";
  }
  clear(player_1);
  clear(player_2);
  return 0;
}

void push_bottom(Deck& player, int val) {
  Node* pNew = new Node{val, nullptr, nullptr};
  if (player.bottom == nullptr) {
    player.bottom = player.top = pNew;
  } else {
    pNew->next = player.bottom;
    player.bottom->pre = pNew;
    player.bottom = pNew;
  }
  ++player.size;
}

void pop_top(Deck& player) {
  Node* tmp = player.top;
  player.top = player.top->pre;
  if (player.size == 1) {
    player.top = player.bottom = nullptr;
  } else {
    player.top->next = nullptr;
  }
  delete tmp;
  --player.size;
}

void clear(Deck& player) {
  Node* tmp;
  while (player.size != 0) {
    tmp = player.top;
    player.top = player.top->pre;
    if (player.size == 1) {
      player.top = player.bottom = nullptr;
    }
    delete tmp;
    --player.size;
  }
}