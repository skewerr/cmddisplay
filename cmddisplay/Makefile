CC=gcc
AR=ar
RLIB=ranlib
CFLAGS=-I.
DEPS = cmddisplay.h cmddraw.h cmdclip.h cmdfill.h cmdobj.h cmdtrf.h cmdmisc.h cmdqueue.h
OBJ = cmddisplay.o cmddraw.o cmdclip.o cmdfill.o cmdobj.o cmdtrf.o cmdmisc.o cmdqueue.o

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) -lm

libcmddisplay.a: $(OBJ)
	$(AR) -cvq $@ $^
	$(RLIB) $@

install:
	mv libcmddisplay.a /usr/local/lib
	cp *.h /usr/local/include

clean:
	rm *.o
