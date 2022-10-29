/* Real Clutered Linked List */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


typedef struct Node{
  void* data;
  struct Node* next;
} Node;

typedef struct Linked_List{
  int size;
  Node* head;
} Linked_List;


int init_list(Linked_List* l) {
  l->size = 0;
  l->head = NULL;
  return 0;
}

/* Add node to beginning of linked list
   Param l: linked list we want to add to
   Param d: data we want to add
   Param s: size of data we want to add
 */
int list_push(Linked_List* l, void* new_data, size_t new_data_size) {
  Node* new_node = malloc(sizeof(Node));
  if(new_node != NULL){
    new_node->data = malloc(new_data_size);
    if(new_node->data != NULL) {
      memcpy(new_node->data,new_data,new_data_size);
    }
    new_node->next = l->head;
    l->head = new_node;
    l->size++;
    return 0;
  }
  else
    return -1;
}

int list_add(Linked_List* l, void* new_data, size_t new_data_size) {  
  return 0;
}

int list_remove(Linked_List* l){
  Node* n = l->head;
  while(n->next->next != NULL){
    n = n->next;
  }
  free(n->next);
  n->next = NULL;
  return 0;
}

int list_pop(Linked_List* l) {
  Node* head = l->head;
  l->head = head->next;
  l->size--;
  free(head);
  return 0;
}

void print_list(Linked_List* l, void (*print_fun)(void *)) {
  Node* n = l->head;
  while(n != NULL) {
    (print_fun)(n->data);
    n = n->next;
  }
}

// cast void* to int* then dereference
void print_int(void* x){
  printf("%d\n",*(int*)x);
}


int main() {
  Linked_List* l = malloc(sizeof(Linked_List));
  init_list(l);
  int arr[] = {2, 4, 6, 8, 10};
  for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
    list_push(l, &arr[i], sizeof(arr[0]));
  }
  printf("Before pop\n");
  print_list(l, print_int);
  list_pop(l);
  printf("List size: %d\n", l->size);
  printf("After pop\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);
  list_remove(l);
  printf("After remove\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);

  return 0;
}
