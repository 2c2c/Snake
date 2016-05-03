#include <stdio.h>
#include <stdlib.h>


typedef struct Point {
  int x;
  int y;
} Point;

typedef struct Node {
  struct Node *next;
  Point value;
} Node;

typedef enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
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

Snake *init_snake() {
  Node *head = NULL;
  Point p = { 0,0 };
  add_front(&head, p);
  // Snake snake = { 'r', 1, head };
  Snake *snake = (Snake *)malloc(sizeof(Snake));
  snake->direction = RIGHT;
  snake->size = 1;
  snake->head = head;
  return snake;
}

void update_snake(Snake *snake) {
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
    //death
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

int is_snake_collision(Snake *snake, Point pos) {
  while (snake->head) {
    if (is_same_point(snake->head->value, pos)) {
      return 1;
    }
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  Node *head = NULL;
  Snake *snake = init_snake();

  int i;
  for (i = 0; i <= 10; i++) {
    Point p = { i, i };
    add_front(snake->head, p);
  }
  Point q = { 10, 10 };
  return 0;
}