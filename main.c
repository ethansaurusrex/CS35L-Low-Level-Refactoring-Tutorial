/* Real Clutered Linked List */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/* *****Generic Singly Linked List*****
   
   Allows arbitrary data to be inserted into the list,
   this is done
*/
// Node struct typedef
typedef struct Node{
  void* data;
  struct Node* next;
} Node;

// Linked_List struct typedef
typedef struct Linked_List{
  int size;
  Node* head;
} Linked_List;

// Initialize the linked list, returns 0 on success
int init_list(Linked_List* l) {
  l->size = 0;
  l->head = NULL;
  return 0;
}

// Add node to beginning of linked list, returns 0 on success and -1 otherwise
int list_push(Linked_List* l, void* new_data, size_t new_data_size) {
  Node* new_node = malloc(sizeof(Node));
  if(new_node == NULL)
    return -1;
  new_node->data = malloc(new_data_size);
  if(new_node->data == NULL)
    return -1;
  // here we use <string.h>'s memcpy to "manually" write the proper number of \
  // bytes to the location we want. memcpy takes in a destination pointer, a \
  // source pointer, and a number of bytes. We pass in the void* data field we \
  // want to change, the void* data we want to change it to, and the size of \
  // that data.
  memcpy(new_node->data,new_data,new_data_size);
  // NOTE: ^ above, we could also copy the data byte by byte using a for loop \
  // as follows:
  /*
    for(int i = 0; i < new_data_size; i++)
        *(uint8_t*)(new_node->data + i) = *(uint8_t*)(new_data + i);

    Breakdown of code:
    -uint8_t, an 8-bit unsigned integer will just contain the data we
     want to copy over so we work in bytes, this lets the compiler know
     the proper offsets we want to work with (in terms of bytes).
    -(new_node->data +i) & (new_data + i), since these are each pointers
     we are adding an offset from their memory location, if new_node->data 
     was a char*, we use offsets just as if it were an array: 0 offset for
     the first byte, 1 offset for the next byte and so on.
    -The dereference operator *, allows us to read and write the actual value
     which the pointer is pointing to. 

     If we consult this fancy table https://en.cppreference.com/w/c/language/operator_precedence
     we can then break down the expression. Since both the left and right
     handsides are effectively the same operation and both sides contain operators
     of higher precedence than the assignment operator, =, we can just focus on
     the left hand side.

    Order of Operation

     Expression: *(uint8_t*)(new_node->data + i)
     1. (new_node->data + i)     ==> parentheses are evaluated first (1st section of table)
     2. new_node->data + i       ==> structure access, ->, is evaluated. We have void* data now
     3. data + i                 ==> binary addition operator, offset address by i
     4. *(uint8_t*)(OFFSET_ADDR) ==> casts and dereferences (2nd section) have same
                                     precedence but have right-to-left associativity
				     so we evaluate right to left
     5. (uint8_t*)(OFFSET_ADDR)  ==> cast OFFSET_ADDR calculated in 1-3, to uint8_t *
     6. *(CASTED_OFFSET_ADDR)    ==> now we can dereference the newly cast, offset address

    Conclusion:
     It is easier to use memcpy, but it is good practice to know how functions like these work. 

   */
  new_node->next = l->head;
  l->head = new_node;
  l->size++;
  return 0;
}

// add Node to the back of the list, returns 0 on success and -1 otherwise
int list_add(Linked_List* l, void* new_data, size_t new_data_size) {  
  Node* new_node = malloc(sizeof(Node));
  Node* n = l->head;
  if(new_node == NULL)
    return -1;
  while(n->next != NULL){ // walk to last node, then add new_node
    n = n->next;
  }
  new_node->data = malloc(new_data_size);
  if(new_node == NULL)
    return -1;
  // set data for new_node and set next pointer to NULL
  memcpy(new_node->data,new_data,new_data_size);
  new_node->next = NULL;
  // set next node
  n->next = new_node;
  l->size++;
  return 0;
}

// remove Node from front of the list, return data of Node
// Notice we are returning a void*, this way a user can handle \
// how we want to process the popped data
// In the main function you can see how we dereference a cast to int*
void* list_pop(Linked_List* l) {
  Node* head = l->head;
  void* data = head->data;
  l->head = head->next;
  l->size--;
  free(head);
  return data;
}

// remove Node from back of the list, return success code
// No values is returned here, this could be different to match \
// pop, but instead it will not
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

// Here we have a print list function that accepts a list and a \
// function pointer to a printing function. This printing function \
// will walk from down the list from head to tail (NULL), while \
// printing the elements. Notice the parameter of the function is \
// void*, this will be cast to the proper type in the actual function \
// similar to the Node, it allows us to pass in any type we want.
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


/* *****Integer Stack Implementation using Linked_List*****
   
   Will have init, push, pop, and size functions
 */

// Stack struct typedef
typedef struct Stack{
  Linked_List* list;
} Stack;

// Initialize the stack using Linked_List's init function
int stack_init(Stack* s) {
  Linked_List *l = malloc(sizeof(Linked_List)); //allocate some data for our linked list
  s->list = l; // point to that newly allocated space
  init_list(s->list); // initialize that Linked_List's members
  return 0;
}

// just calls linked_list push
int stack_push(Stack* s, int x) {
  x = list_push(s->list, &x, sizeof(int));
  return x;
}

// just calls linked_list pop
// casting the void* to int* then we dererefence the \
// pointer using * again to retrieve the actual value \
// the pointer points to
int stack_pop(Stack* s) {
  int data = *(int *)list_pop(s->list); 
  return data;
}

// returns the size of the stack, uses the linked list
int stack_size(Stack *s) {
  return s->list->size;
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
