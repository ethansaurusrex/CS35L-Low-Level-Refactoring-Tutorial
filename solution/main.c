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

// maybe you can implement a stack_peak function here?

/* Main function containing driver code */
int main() {
  /* Linked_List demo */
  Linked_List* l = malloc(sizeof(Linked_List));
  int arr[] = {2, 4, 6, 8, 10};
  int new_add = 3;
  int new_push = 7;
  printf("------START OF LINKED LIST DEMO------\n"); 
  printf("Initializing list\n");
  init_list(l);

  for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
    printf("Adding value %d to list...\n", arr[i]);
    list_push(l, &arr[i], sizeof(arr[0])); //adding the pointer to the value!
  }

  printf("\nPrinting list\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);

  printf("\n*****\nPopping stack, popped value: %d\n*****\n", *(int *)list_pop(l));
  printf("Printing list\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);

  printf("\n*****\nRemoving from back of list\n*****\n");
  list_remove(l);
  printf("Printing list\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);

  printf("\n*****\nPushing %d to front of list\n*****\n", new_push);
  list_push(l, &new_push, sizeof(new_push));
  printf("Printing list\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);

  printf("\n*****\nAdding %d to back of list\n*****\n", new_add);
  list_add(l, &new_add, sizeof(new_add));
  printf("Printing list\n");
  print_list(l, print_int);
  printf("List size: %d\n", l->size);
  printf("------END OF LINKED LIST DEMO------\n"); 
  

  /* Stack demo */
  printf("\n------START OF STACK DEMO------\n"); 
  Stack* stacc = malloc(sizeof(Stack));
  int new_arr[] = {1,3,5,7};
  printf("Initializing stack\n");
  stack_init(stacc);
  
  printf("Pushing to stack, %d\n", new_arr[0]);
  stack_push(stacc, new_arr[0]);
  printf("Pushing to stack, %d\n", new_arr[1]);
  stack_push(stacc, new_arr[1]);
  printf("Pushing to stack, %d\n", new_arr[2]);
  stack_push(stacc, new_arr[2]);
  
  printf("Stack size is %d\n", stack_size(stacc));
  printf("Popping stack, popped value %d\n", stack_pop(stacc));
  printf("Stack size is %d\n", stack_size(stacc));
  printf("Popping stack, popped value %d\n", stack_pop(stacc));
  printf("Stack size is %d\n", stack_size(stacc));
  printf("Pushing to stack, %d\n", new_arr[3]);
  stack_push(stacc, new_arr[3]);
  printf("Popping stack, popped value %d\n", stack_pop(stacc));
  printf("------END OF STACK DEMO------\n"); 
  
  
  return 0;
}
