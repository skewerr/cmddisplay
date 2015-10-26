prefix=/usr/local

CC=gcc

override CFLAGS+=-I.
override LDLIBS+=-lm

OBJECTS=display.o draw.o clip.o misc.o
INCLUDES=display.h draw.h clip.h misc.h

# Compilation.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Archiving into static library file.
libcmddisplay.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

# These aren't file targets.
.PHONY: install clean

install:
	install -d $(prefix)/lib $(prefix)/include/cmddisplay
	install -m 0644 libcmddisplay.a $(prefix)/lib
	install -m 0644 *.h $(prefix)/include/cmddisplay

clean:
	$(RM) *.o
