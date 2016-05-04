#include "list.h"

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
void display_list(Node *head) {
  Node *current_node = head;
  while (current_node) {
    printf("(%d, %d) ->", current_node->value.x, current_node->value.y);
    current_node = current_node->next;
  }
  printf("NULL\n");
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
