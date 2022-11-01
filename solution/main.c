/* Real Clutered Linked List */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "linked_list.h"
#include "stack.h"

// cast void* to int* then dereference
void print_int(void* x){
  printf("%d\n",*(int*)x);
}



/* Main function containing driver code */
int main() {
  /* Linked_List demo */
  Linked_List* l = malloc(sizeof(Linked_List));
  int arr[] = {2, 4, 6, 8, 10};
  int new_add = 3;
  init_list(l);
  
  for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
    list_push(l, &arr[i], sizeof(arr[0]));
  }
  
  printf("Before pop\n");
  print_list(l, print_int);
  printf("*****\nPopped %d\n*****\n", *(int *)list_pop(l));
  printf("List size: %d\n", l->size);
  printf("After pop\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);
  list_remove(l);
  printf("After remove\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);
  list_add(l, &new_add, sizeof(new_add));
  printf("After add\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);
  

  /* Stack demo */
  Stack* stacc = malloc(sizeof(Stack));
  stack_init(stacc);
  stack_push(stacc, 1);
  stack_push(stacc, 7);
  printf("Stack size is %d\n", stack_size(stacc));
  printf("Popping stack %d\n", stack_pop(stacc));
  printf("Stack size is %d\n", stack_size(stacc));
  
  
  
  return 0;
}
