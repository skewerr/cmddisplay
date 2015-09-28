#ifdef _WIN32
#include <windows.h>
#else
#include <stdio.h>
#endif

#include "misc.h"

void set_cursor (int x, int y)
{
#ifdef _WIN32
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("\033[%d;%dH", y+1, x+1);
#endif
}

void switch_value (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
