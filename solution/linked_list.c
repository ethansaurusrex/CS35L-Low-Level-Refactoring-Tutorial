
#include "linked_list.h"

#include <stdlib.h> //free
#include <string.h> //memcpy

int init_list(Linked_List* l) {
  l->size = 0;
  l->head = NULL;
  return 0;
}

int list_push(Linked_List* l, void* new_data, size_t new_data_size) {
  Node* new_node = malloc(sizeof(Node));
  if(new_node == NULL)
    return -1;
  new_node->data = malloc(new_data_size);
  if(new_node->data == NULL)
    return -1;
  memcpy(new_node->data,new_data,new_data_size);
    new_node->next = l->head;
  l->head = new_node;
  l->size++;
  return 0;
}

int list_add(Linked_List* l, void* new_data, size_t new_data_size) {  
  Node* new_node = malloc(sizeof(Node));
  Node* n = l->head;
  if(new_node == NULL)
    return -1;
  while(n->next != NULL){
    n = n->next;
  }
  new_node->data = malloc(new_data_size);
  if(new_node == NULL)
    return -1;
  memcpy(new_node->data,new_data,new_data_size);
  new_node->next = NULL;
  n->next = new_node;
  l->size++;
  return 0;
}

void* list_pop(Linked_List* l) {
  Node* head = l->head;
  void* data = head->data;
  l->head = head->next;
  l->size--;
  free(head);
  return data;
}

int list_remove(Linked_List* l){
  Node* n = l->head;
  while(n->next->next != NULL){
    n = n->next;
  }
  free(n->next);
  n->next = NULL;
  l->size--;
  return 0;
}

void print_list(Linked_List* l, void (*print_fun)(void *)) {
  Node* n = l->head;
  while(n != NULL) {
    (print_fun)(n->data);
    n = n->next;
  }
}
