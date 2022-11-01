CC=$(shell if which gcc > /dev/null; \
	   then echo gcc; exit; \
	   elif which clang > /dev/null; \
	   then echo clang; exit; \
	   else \
	   echo "Error no GCC or Clang on system" 1>&2; \
	   exit 1; \
	   fi)

main: main.o linked_list.o stack.o
	$(CC) main.o linked_list.o stack.o -o $@

main.o: main.c
	gcc -c main.c

linked_list.o: linked_list.h linked_list.c
	gcc -c linked_list.c

stack.o: stack.h stack.c
	gcc -c stack.c

.PHONY: clean

clean:
	rm *.o main
