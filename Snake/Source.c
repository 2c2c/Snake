#include <stdio.h>
#include <stdlib.h>

// TODO return array of current snake node positions
// TODO print board (whatever isnt snake or food is empty..)

typedef struct Point {
  int x;
  int y;
} Point;

typedef struct Food { Point pos; } Food;

typedef struct Node {
  struct Node *next;
  Point value;
} Node;

typedef enum Direction { UP, DOWN, LEFT, RIGHT } Direction;

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
  Point p = {rand() % 10, rand() % 10};
  while (is_snake_collision(snake, p) || is_same_point(p, food->pos)) {
    p.x = rand() % 10;
    p.y = rand() % 10;
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

void update_snake(Snake *snake, Food *food) {
  Point pos = snake->head->value;
  switch (snake->direction) {
  case UP:
    pos.y++;
  case DOWN:
    pos.y--;
  case LEFT:
    pos.x--;
  case RIGHT:
    pos.x++;
  }

  // out of bounds TODO upper limit
  if (pos.x < 0 || pos.y < 0) {
    // global variable indicating death?
  }
  if (is_snake_collision(snake, pos)) {
    // death
  }
  // eat
  if (is_same_point(pos, food->pos)) {
    // TODO increase score

    // update_food has logic to ensure it doesn't respawn in same loc.
    // by calling it first we remove chance of appending head of snake on top of
    // a food position
    update_food(food, snake);
    add_front(snake->head, pos);
  }
}

void remove_duplicates(Node **head) {
  Node *current_node = (*head);
  Node *previous_node = NULL;

  while (current_node->next) {
    previous_node = current_node;
    current_node = current_node->next;
    if (is_same_point(previous_node->value, current_node->value)) {
      previous_node->next = current_node->next;
      current_node->next = NULL;
      current_node = previous_node;
    }
  }
  return;
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
  for (i; i < 10; i++) {
    for (j; j < 10; j++) {
      Point p = {i, j};
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

// add node to internal list, increment snake size count
void grow_snake(Snake *snake, Point pos) {
  add_front(&snake->head, pos);
  snake->size++;
}

int main(int argc, char const *argv[]) {
  Node *head = NULL;
  Snake *snake = init_snake();
  Food *food = init_food(snake);

  int i;
  for (i = 0; i < 10; i++) {
    Point p = {i, i};
    grow_snake(snake, p);
  }
  Point *positions = snake_positions(snake);
  print_board(snake, food);

  // Point q = {10, 10};
  return 0;
}