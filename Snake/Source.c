#include "list.h"
#include "snake.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// wow much cross platform
#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#define getch() _getch()
#define sleep(x) Sleep(x)
#else
#include <ncurses.h>
#include <unistd.h>
#endif

void direction(Snake *snake) {
  char c;
  c = getch();
  change_direction(snake, c);
}

void game_loop(Snake *snake, Food *food) {
  update_snake(snake, food);
  print_board(snake, food);
  sleep(300);
}

int main(int argc, char const *argv[]) {
  srand((unsigned int)time(NULL));
  Snake *snake = init_snake();
  Food *food = init_food(snake);

#pragma omp parallel sections
  {
#pragma omp section
    {
      while (snake->alive)
        direction(snake);
    }
#pragma omp section
    {
      while (snake->alive)
        game_loop(snake, food);
    }
  }
  return 0;
}