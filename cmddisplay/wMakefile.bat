@ECHO off

set PATH=%PATH%;C:\MinGW\bin
set OBJ=cmddisplay.o cmddraw.o cmdclip.o cmdfill.o cmdobj.o cmdmisc.o cmdqueue.o cmdtrf.o

if /I "%1" == "default" goto :default
if /I "%1" == "install" goto :install
if /I "%1" == "clean" goto :clean

:default
echo Compiling .c files...

for %%A in (
    cmddisplay.c,
    cmddraw.c,
    cmdclip.c,
    cmdfill.c,
    cmdqueue.c,
    cmdobj.c,
    cmdtrf.c,
    cmdmisc.c
) do gcc -c %%A

echo Archiving .o files...

ar -cvq libcmddisplay.a %OBJ%
ranlib libcmddisplay.a

echo Done.
goto :eof

:install
echo Installing to C:\MinGW\lib and C:\MinGW\include...
move libcmddisplay.a C:\MinGW\lib\libcmddisplay.a
copy *.h C:\MinGW\include\
echo Done.
goto :eof

:clean
echo Deleting .o files...
del *.o
echo Done.
goto :eof
