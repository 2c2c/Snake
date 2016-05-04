#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 5 rows
// 8 cols
#define X_MAX 8
#define Y_MAX 5

// out of game vs ingame
#define LIVE 0

typedef struct Point {
  int x;
  int y;
} Point;

typedef struct Food { Point pos; } Food;

typedef struct Node {
  struct Node *next;
  Point value;
} Node;

typedef enum Direction {
  UP = 'u',
  DOWN = 'd',
  LEFT = 'l',
  RIGHT = 'r'
} Direction;

typedef struct Snake {
  Direction direction;
  size_t size;
  Node *head;
} Snake;

int is_same_point(Point a, Point b) {
  if (a.x == b.x && a.y == b.y) {
    return 1;
  }
  return 0;
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

void add_front(Node **head, Point value) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->value = value;
  if (!(*head)) {
    new_node->next = NULL;
    (*head) = new_node;
  } else {
    new_node->next = (*head);
    (*head) = new_node;
  }
  return;
}

// add node to internal list, increment snake size count
void grow_snake(Snake *snake, Point pos) {
  add_front(&snake->head, pos);
  snake->size++;
}

void remove_link(Node **head, Point value_to_remove) {
  Node *temp_node = NULL;
  Node *current_node = (*head);
  if (is_same_point((*head)->value, value_to_remove)) {
    (*head) = (*head)->next;
  } else {
    while (current_node) {
      if (is_same_point(current_node->value, value_to_remove)) {
        temp_node = current_node->next;
        current_node->next = NULL;
        current_node = temp_node;
      }
      current_node = current_node->next;
    }
  }
  return;
}

void display_list(Node *head) {
  Node *current_node = head;
  while (current_node) {
    printf("(%d, %d) ->", current_node->value.x, current_node->value.y);
    current_node = current_node->next;
  }
  printf("NULL\n");
}

void update_food(Food *food, Snake *snake) {
  Point p = {rand() % X_MAX, rand() % Y_MAX};

  // a better implementation might be needed if there's performance issues when the board is filled up with snake positions
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
  return snake;
}

// update direction on snake. if direction is opposite current direction, dont do anything.
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
  }

  // out of bounds TODO upper limit
  if (pos.x < 0 || pos.y < 0 || pos.x > X_MAX || pos.y > Y_MAX) {
    // global variable indicating death?
  } else if (is_snake_collision(snake, pos)) {
    // death
  }
  // eat
  else if (is_same_point(pos, food->pos)) {
    // TODO increase score

    // update_food has logic to ensure it doesn't respawn in same loc.
    // by calling it first we remove chance of appending head of snake on top of
    // a food position
    update_food(food, snake);
    grow_snake(snake, pos);
  }
  // move snake: head takes new point position and the body 'follows' by taking
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
  Point *snake_pos = snake_positions(snake);
  int i = 0;
  int j = 0;
  for (i; i < Y_MAX; i++) {
    for (j; j < X_MAX; j++) {
      Point p = {j, i};
      if (is_snake_collision(snake, p)) {
        printf("S");
      } else if (is_same_point(food->pos, p)) {
        printf("F");
      } else {
        printf("x");
      }
    }
    printf("\n");
    j = 0;
  }
}

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