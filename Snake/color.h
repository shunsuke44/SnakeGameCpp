#ifndef INCLUDED_COLOR_H_
#define INCLUDED_COLOR_H_

#include <curses.h>

#define C_DEFAULT COLOR_PAIR(0)
#define C_BLACK COLOR_PAIR(1)
#define C_RED COLOR_PAIR(2)
#define C_GREEN COLOR_PAIR(3)


void set_color();

#endif // INCLUDED_COLOR_H_
