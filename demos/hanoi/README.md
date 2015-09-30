hanoi
=====

Just a graphical representation of Hanoi's Tower.

It works!

To compile it, first you should make a static library
called `libstack.a` from `lib/stack/stack.c|h`. Leave
it in the `lib` folder. `libcmddisplay.a`, which you
can get from running `make` in the `cmddisplay` directory
should either be installed with `make install` or put in
the `lib` folder.

Then, `cc -o hanoi hanoi.c tower.c -Iinclude -Llib -lcmddisplay -lstack`
