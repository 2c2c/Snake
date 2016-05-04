#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "snake.h"

int main(int argc, char const *argv[]) {
  srand((unsigned int)time(NULL));
  Snake *snake = init_snake();
  Food *food = init_food(snake);

  char c;
  while (1) {
    print_board(snake, food);
    scanf_s(" %c", &c);
    change_direction(snake, c);
    update_snake(snake, food);
  }

  // Point q = {10, 10};
  return 0;
}