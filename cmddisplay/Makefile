CC=gcc
AR=ar
RLIB=ranlib
CFLAGS=-I.
DEPS = cmddisplay.h cmddraw.h cmdclip.h misc.h
OBJ = cmddisplay.o cmddraw.o cmdclip.o misc.o

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

libcmddisplay.a: $(OBJ)
	$(AR) -cvq $@ $^
	$(RLIB) $@

clean:
	rm *.o
