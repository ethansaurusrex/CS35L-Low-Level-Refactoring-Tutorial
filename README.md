# Refactoring Practice

This is a small practice example where we will walk through the process of refactoring some cluttered code as well as writing a suitable Makefile for the refactored files. This will give you some practice for Lab 5 where we will complete a similar task, yet more complex task.

To start download the 5 files, main.c, linked_list.h, linked_list.c, stack.h, and stack.c.

Opening the files you'll notice that linked_list.h and stack.h contain nothing but some header guards and comments while their respective .c files contain just comments. Navigating to the main.c you'll find some overly-commented code describing the linked list and stack implementations.

## Basic Code Overview

  
Say something about organization

  

### Linked List

  

The linked list code consists of a `Linked_List` structure, a `Node` structure and some functions for the linked list. The `Node` structure contains some data of type `void*` (we'll get to why later), and a pointer to the next `Node` in the list. The `Linked_List` structure just keeps track of both the head of the list using a pointer to a `Node` and the size of the list. Together these two structures allow us to put together an implementation of a **generic** Linked List, that is, a list that can accept a pointer to any type as the data. This means we not only could store anything we want, ranging from characters to custom structures, but we could also utilize this singly linked list to implement a number of other data structures such as a hash map, in which the entries of the map are linked lists and each piece of data is a key-value pair. In our case, we use the linked list to implement a stack.

  

While most linked lists data structures contain some kind of function to delete entries based on data values, this implementation only contains a push, pop, add, and delete function. The former two add and remove from the front of the list, the latter two do the same from the back of the list. You can see how each one is implemented in the code. In addition to these functions there is a print function that accepts a function pointer to a void function pointer which itself accepts a void pointer.

  

The `void*` allows us to pass in a pointer of any type, the only work we have to do is write a function to print the type out.

  

### Stack

  

The stack code consists of a `Stack` structure, which contains a single `Linked_List`. Since stacks typically only have push and pop functions, we emulate them here by creating functions called `stack_push` and `stack_pop`, which are each just wrappers for the linked list push and pop functions instead we no have them accept integral values. Here we are narrowing down the generic linked list to a stack of integers.

  

 
### Void* and Generic C-Code

  

C, lacking the templates of C++, has to find a more hack-y way of allowing generic types. One? such workaround is using void pointers. Void pointers or `void*` are pointers that have no associated data type, they can be assigned any type of pointer. When we dereference them to assign a value or read the value we have to cast them to the type we want. In the context of this code, we see in the struct `Node`, we have a `void*` data member. Combined with our `list_add` and `list_push` methods we simply save the passed in data to the proper location by using `memcpy`. This saves us some time and has better readability (see comment in code). This allows us to use

  

Now as for the generic prints we can see an int_print function accepts `void*` or a pointer to some arbitrary data. We cast the value to actually print out the data.

  
## Refactoring

  

Now for a small program our organization might be fine, but if we left it this way there would be no exercise. In addition, we might want to use this implementation in the future; we want **reusable** code. So lets start off with a short and shallow review of header files in C.

  

### Header Files

  

Header files in C differ from their gnarly cousin C++ in one main way:

Declarations and Implementations are in *seperate* files. Meaning that,
1. Header files or .h files will contain: function prototypes, `typdefs`, struct and variable declarations, `#defines`, macros, and more

2. Implementation files or .c files will contain: function definitions/implementations.

  
  

Below is a small example of a proper header and implementation file:

  
-----------
dummy.h
```c
#ifndef __DUMMY_H__
#define __DUMMY_H__

#include <stddef.h>


uint8_t dumdum(uint8_t a);


#endif 
```

--------------

  

dummy.c

  
```c
#include "dummy.h"

#include <stdio.h>

  
uint8_t dumdum(uint8_t a) {
	printf("Returning a\n");
	return a;
}
```


-------------

  

Notice how we include `stddef.h` in the header file and both dummy.h and stdio.h in the implementation file.

  

The trick for this is noticing that we use uint8_t as the return type and parameter to our single function declaration. We want to make the header files as compact as possible, so the golden rule(s) I follow are

-   Only include files in the header if it is necessary to be able to declare your functions, macros, variables, etc, inside the header.
-   Include any extra headers you need to define the function, inside the implementation file.

  
In the example, we only include `stddef.h` in the `dummy.h` since our prototypes use uint8_t. In the implementation file we have already included `dummy.h`, which itself contains `stddef.h` so we don't need to re-include it. Now since we use the `printf` function and therefore we must include `stdio.h`.

### Declutering

Let's navigate to the `linked_list.h` file in the directory. You should see something like this
```c
linked_list.h
#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__


#endif
```

Inside these header guards we want to place our typedefs and prototypes pertaining to the linked list data structure. One way we can do this is copy **everything** relating to the data structure, then deleting the definition portion of each function. Or you can open up the two files side by side and just rewrite them. Anyway you choose, find a way to put the code in the header file. You should end up with something like this (with comments removed).

```c
//linked_list.h
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
```

See now, we have prototypes **and** structures in the header file. This allows us to compartmentalize code and reuse our structures for future code. In addition, one can see we have included `<stddef.h>` since our prototypes for `list_push` and `list_add` use parameters of type `size_t`.

Now, for the implementation code, your `linked_list.c` should be completely empty save for a comment.

We now want to place our implementations inside this file. That is, the whole function as it is shown in the `main.c` file.

```c
//linked_list.c

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

```

Notice we neglected to place `void print_int(void *x)` into either file. Why? Since print_int is not generalized we want to keep it seperate. In a way, we could treat it as a user-defined function that we want to pass into our generic data structure. For this exercise we will keep it in the main.c, though we could put it in its own file to be neat.

Great! Now our `main.c` has been made much cleaner. We can simply add in our header file, and now let's run it to make sure everything works.

If you read the compile.txt file you will see some terrible instructions on how to compile and run our code. **HINT** we might want to find a better way of doing this. For now, lets run the command given:

```bash
main.c -o main
/usr/bin/ld: /tmp/cc2KW7RN.o: in function `stack_init':
main.c:(.text+0x60): undefined reference to `init_list'
/usr/bin/ld: /tmp/cc2KW7RN.o: in function `stack_push':
main.c:(.text+0x95): undefined reference to `list_push'
/usr/bin/ld: /tmp/cc2KW7RN.o: in function `stack_pop':
main.c:(.text+0xbc): undefined reference to `list_pop'
/usr/bin/ld: /tmp/cc2KW7RN.o: in function `main':
main.c:(.text+0x13c): undefined reference to `init_list'
/usr/bin/ld: main.c:(.text+0x16b): undefined reference to `list_push'
/usr/bin/ld: main.c:(.text+0x196): undefined reference to `print_list'
/usr/bin/ld: main.c:(.text+0x1a2): undefined reference to `list_pop'
/usr/bin/ld: main.c:(.text+0x1ef): undefined reference to `print_list'
/usr/bin/ld: main.c:(.text+0x214): undefined reference to `list_remove'
/usr/bin/ld: main.c:(.text+0x233): undefined reference to `print_list'
/usr/bin/ld: main.c:(.text+0x264): undefined reference to `list_add'
/usr/bin/ld: main.c:(.text+0x283): undefined reference to `print_list'
collect2: error: ld returned 1 exit status
```

Oh no.

The main code has no clue what these linked list functions are. We have to compile our `linked_list.c` file along with the rest of our code.

```bash
$> gcc linked_list.c main.c -o main
$> ./main
.
.
.
```

I have removed the output, but you'll see the same output as before.

Continuing on, we want to repeat this process once more for the stack data structure code.

```c
//stack.h
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
```

We once again follow the same rules of only including files that are needed for prototypes in the `.h` file, and including files needed for implementations in the `.c` files.

Note also how we are including `linked_list.h` in the stack header file. Thanks to those header guards we won't have circular includes when we decide to compile.


```c
//stack.c
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
```

What clean and tidy code. While the implementation leaves more to be desired, no one can complain about the code's organization. All that's left to do is compile it and check the output.

Following the method from before, we want to add `stack.c` in our line when we compile the code.

```bash
$> gcc main.c linked_list.c stack.c -o main
$> ./main
.
.
.
```

Again, the output is omitted since it is quite large.

Now, I tend to not just want the executable but also the `.obj` files. So I could run something like:

```bash
$> gcc -c main.c
$> gcc -c linked_list.c
$> gcc -c stack.c
$> ls *.o
main.o	linked_list.o  stack.o
$> gcc main.o linked_list.o stack.o -o main
$> ./main
.
.
.
```

Wow, that was a lot to type just to get the .o files and the final executable, if only there were a quicker way of doing th–

## Makefiles

Makefiles make the job of compiling, installing, testing, and using software, easy. When it comes to compiled software, there are many variables that need be taken into account to properly run the code on a system. These could be as simple as the version of a compiler to as complex as the chipset and architecture of a machine. Make and Makefiles allow logic to be written that can then build, run, and test our program.

In the context of this small program we are tired of typing out the same commands over and over again.

I will be using Makefile terminology so if you need to refresh you can read up here https://makefiletutorial.com/

Let's start with something small

```makefile
main:
	gcc main.c linked_list.c stack.c -o $@

```

Make's default target is the first target, in this case main.

The odd character `$@` is similar to shell scripts where we evaluate variables using the dollar sign. In make, the `@` symbol is a variable that holds the name of the current target. In our case we are naming our executable `main`, the name of the only target we have. Note: we can run shell scripts inside the makefile but note that single dollar signs `$` evaluate make variables and double dollar signs `$$` evaluate shell variables. This *may* be helpful later.

Let's improve this,

```makefile
main:
	gcc main.c linked_list.c stack.c -o $@

main.o: main.c
	gcc -c main.c

linked_list.o: linked_list.h linked_list.c
	gcc -c linked_list.c

stack.o: stack.h stack.c
	gcc -c stack.c
```