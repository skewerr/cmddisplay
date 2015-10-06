@ECHO off

set PATH=%PATH%;C:\MinGW\bin
set OBJ=

if /I "%1" == "default" goto :default
if /I "%1" == "clean" goto :clean

:default
echo Compiling stack files...

gcc -o lib\stack\stack.o -c lib\stack\stack.c
ar -cvq lib\libstack.a lib\stack\stack.o
ranlib lib\libstack.a

echo Compiling hanoi.c and tower.c...

gcc hanoi.c tower.c -o hanoi -Iinclude -Llib -lstack -lcmddisplay

echo Done.
goto :eof

:clean
echo Deleting .o files...
del lib\stack\*.o
echo Done.
goto :eof
