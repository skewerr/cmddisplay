#ifdef _WIN32
#include <windows.h>
#else
#include <stdio.h>
#endif

#include <stdlib.h>

#include "misc.h"

#define true    1
#define false   0

/*
 * These are miscellaneous functions to be used by other units in this library.
 * The functions are as follows:
 *
 * misc_clear_scr - clears the screen only once, then stops.
 * misc_set_cursor - sets cursor position in console.
 * misc_switch_val - switches the value of two int variables pointed to.
 *
 * Some functions are so short they were made inline functions, defined in the
 * associated header file. There are comments in it to explain their purpose.
 */

void
misc_clear_scr(void)
{
    static short cleared = false;

    if(!cleared)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        cleared = true;
    }
}

void
misc_set_cursor(int x, int y)
{
#ifdef _WIN32
    COORD coord = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("\033[%d;%dH", y+1, x+1);
#endif
}

void
misc_switch_val(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
