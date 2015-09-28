## Code organization

I'll be using this README to explain how I organize things in
these files. More documentation will go on a wiki, I might
copy this README over there in the future.

## cmddisplay.h and cmddisplay.c

The header file, of course, contains the typedef that defines
the `display` data type. It also has the prototypes for all
the functions that go inside the `.c` file. These are the
most basic functions, which are to be used by the other files
for different reasons. Creating/destroy a display, painting
a "pixel" in it, etc.

## cmddraw.h and cmddraw.h

These will have functions used to draw more complicated things
than pixels on screen. Currently, lines and [TODO] files. I'm
going to try and implement different algorithms.

## cmdclip.h and cmdclip.c

`cmddraw.h|c` will use these to clip shapes and save processing
power, if possible. Now like we'd need to right now, but still.

## misc.h and misc.c

Has functions used by other units in this folder. They're not
really to do with the display, but are still useful to have.
