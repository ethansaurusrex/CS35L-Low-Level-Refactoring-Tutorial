#include "stack.h"

#include <stdlib.h> //malloc


int stack_init(Stack* s) {
  Linked_List *l = malloc(sizeof(Linked_List)); //allocate some data for our linked list
  s->list = l; // point to that newly allocated space
  init_list(s->list); // initialize that Linked_List's members
  return 0;
}

int stack_push(Stack* s, int x) {
  x = list_push(s->list, &x, sizeof(int));
  return x;
}

int stack_pop(Stack* s) {
  int data = *(int *)list_pop(s->list); 
  return data;
}

int stack_size(Stack *s) {
  return s->list->size;
}

