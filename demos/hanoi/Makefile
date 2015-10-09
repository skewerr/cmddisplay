CC=gcc
AR=ar
RLIB=ranlib

target:
	$(CC) -o lib/stack/stack.o -c lib/stack/stack.c
	$(AR) -cvq lib/libstack.a lib/stack/stack.o
	$(RLIB) lib/libstack.a
	$(CC) -o hanoi hanoi.c tower.c -Iinclude -Llib -lstack -lcmddisplay -lm

clean:
	rm lib/stack/*.o
