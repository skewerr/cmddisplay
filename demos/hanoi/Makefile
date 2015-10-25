CC=gcc
CFLAGS=-Iinclude -Llib
LDLIBS=-lstack -lcmddisplay -lm

SOURCE=hanoi.c tower.c

lib/stack.o: lib/stack/stack.c
	$(CC) $(CFLAGS) -c $< -o $@

lib/libstack.a: lib/stack.o
	$(AR) $(ARFLAGS) $@ $<

hanoi: lib/libstack.a
	$(CC) $(CFLAGS) $(SOURCE) $(LDLIBS) -o $@

.PHONY: clean
clean:
	$(RM) lib/*.o
