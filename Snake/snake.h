#ifndef SNAKE_H
#define SNAKE_H
#include "list.h"

// out of game vs ingame

#define X_MAX 8
#define Y_MAX 5

typedef struct Food { Point pos; } Food;

// setting the enum values to respective chars makes testing with stdin simple
typedef enum Direction {
  UP = 'w',
  DOWN = 's',
  LEFT = 'a',
  RIGHT = 'd'
} Direction;

typedef struct Snake {
  int alive;
  Direction direction;
  size_t size;
  Node *head;
} Snake;

int is_snake_collision(Snake *snake, Point pos);
void grow_snake(Snake *snake, Point pos);
void update_food(Food *food, Snake *snake);
Food *init_food(Snake *snake);
Snake *init_snake();

void clear();

// update direction on snake. if direction is opposite current direction, dont
// do anything.
void change_direction(Snake *snake, Direction new_dir);

// remember: matrix based coordinate system
void update_snake(Snake *snake, Food *food);

// array of coordinates snake occupies. Must Free
Point *snake_positions(Snake *snake);

// TOOD pretty
void print_board(Snake *snake, Food *food);

#endif SNAKE_H
