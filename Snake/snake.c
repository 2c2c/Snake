#include "snake.h"

void clear() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
  system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
  system("cls");
#endif
}

int is_snake_collision(Snake *snake, Point pos) {
  Node *current = snake->head;
  while (current) {
    if (is_same_point(current->value, pos)) {
      return 1;
    } else {
      current = current->next;
    }
  }
  return 0;
}

// add node to internal list, increment snake size count
void grow_snake(Snake *snake, Point pos) {
  add_front(&snake->head, pos);
  snake->size++;
}

void update_food(Food *food, Snake *snake) {
  Point p = {rand() % X_MAX, rand() % Y_MAX};

  // a better implementation might be needed if there's performance issues when
  // the board is filled up with snake positions
  while (is_snake_collision(snake, p) || is_same_point(p, food->pos)) {
    p.x = rand() % X_MAX;
    p.y = rand() % Y_MAX;
  }
  food->pos = p;
}

Food *init_food(Snake *snake) {
  Food *food = (Food *)malloc(sizeof(food));
  // we give a starting point despite calling update_food() right after
  // update_food has a condition to ensure we don't spawn in the same location
  Point p = {0, 0};
  food->pos = p;
  update_food(food, snake);
  return food;
}

Snake *init_snake() {
  Node *head = NULL;
  Point p = {0, 0};
  add_front(&head, p);
  Snake *snake = (Snake *)malloc(sizeof(Snake));
  snake->direction = RIGHT;
  snake->size = 1;
  snake->head = head;
  snake->alive = 1;
  return snake;
}

// update direction on snake. if direction is opposite current direction, dont
// do anything.
void change_direction(Snake *snake, Direction new_dir) {
  switch (snake->direction) {
  case UP:
    if (new_dir == DOWN) {
      break;
    }
    snake->direction = new_dir;
    break;
  case DOWN:
    if (new_dir == UP) {
      break;
    }
    snake->direction = new_dir;
    break;
  case LEFT:
    if (new_dir == RIGHT) {
      break;
    }
    snake->direction = new_dir;
  case RIGHT:
    if (new_dir == LEFT) {
      break;
    }
    snake->direction = new_dir;
    break;
  default:
    break;
  }
}

// remember: matrix based coordinate system
void update_snake(Snake *snake, Food *food) {
  Point pos = snake->head->value;
  switch (snake->direction) {
  case UP:
    pos.y--;
    break;
  case DOWN:
    pos.y++;
    break;
  case LEFT:
    pos.x--;
    break;
  case RIGHT:
    pos.x++;
    break;
  default:
    break;
  }

  // losing conditions
  if (pos.x < 0 || pos.y < 0 || pos.x > X_MAX || pos.y > Y_MAX) {
    snake->alive = 0;
  } else if (is_snake_collision(snake, pos)) {
    snake->alive = 0;
  }
  // eating food condition
  else if (is_same_point(pos, food->pos)) {
    // update_food has logic to ensure it doesn't respawn in same loc.
    // by calling it first we remove chance of appending head of snake on top of
    // a food position
    update_food(food, snake);
    grow_snake(snake, pos);
  }
  // move snake condition: head takes new point position and the body 'follows'
  // by taking
  // the previous nodes point
  else {
    Point new_pos = pos;
    Point temp;
    Node *current = snake->head;
    while (current) {
      temp = current->value;
      current->value = new_pos;
      new_pos = temp;
      current = current->next;
    }
  }
}

// array of coordinates snake occupies. Must Free
Point *snake_positions(Snake *snake) {
  Point *positions = (Point *)malloc(sizeof(Point) * snake->size);

  int i = 0;
  Node *current = snake->head;
  while (current) {
    positions[i] = current->value;
    current = current->next;
    i++;
  }
  return positions;
}

// TOOD pretty
void print_board(Snake *snake, Food *food) {
  clear();
  Point *snake_pos = snake_positions(snake);
  int i = 0;
  int j = 0;
  for (i; i < Y_MAX; i++) {
    for (j; j < X_MAX; j++) {
      Point p = {j, i};
      if (is_snake_collision(snake, p)) {
        if (snake->alive) {
          printf("S");
        } else {
          printf("X");
        }
      } else if (is_same_point(food->pos, p)) {
        printf("F");
      } else {
        printf(".");
      }
    }
    printf("\n");
    j = 0;
  }
  if (snake->alive) {
    printf("wasd input \n");
  } else {
    printf("ya lost buddy \n");
  }
}
