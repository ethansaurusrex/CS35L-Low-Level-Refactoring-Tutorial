#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stddef.h>

typedef struct Node{
  void* data;
  struct Node* next;
} Node;

typedef struct Linked_List{
  int size;
  Node* head;
} Linked_List;


int init_list(Linked_List* l);


int list_push(Linked_List* l, void* new_data, size_t new_data_size);


int list_add(Linked_List* l, void* new_data, size_t new_data_size);


void* list_pop(Linked_List* l);


int list_remove(Linked_List* l);


void print_list(Linked_List* l, void (*print_fun)(void *));

#endif
