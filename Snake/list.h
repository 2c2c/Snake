#ifndef LIST_H
#define LIST_H
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

int is_same_point(Point a, Point b);
void add_front(Node **head, Point value);
void display_list(Node *head);
void remove_link(Node **head, Point value_to_remove);
#endif LIST_H
