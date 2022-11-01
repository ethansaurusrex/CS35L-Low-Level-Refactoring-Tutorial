#ifndef __STACK_H__
#define __STACK_H__

#include "linked_list.h"

typedef struct Stack{
  Linked_List* list;
} Stack;

int stack_init(Stack* s);

int stack_push(Stack* s, int x);

int stack_pop(Stack* s);

int stack_size(Stack *s);

#endif
