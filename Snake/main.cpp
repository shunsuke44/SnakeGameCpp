#include <conio.h>
#include <curses.h>
#include <Windows.h>

#include "color.h"
#include "snake.h"

#define WIDTH 40
#define HEIGHT 20

void init() {
	initscr();
	start_color();
	set_color();
}

int main() {
	init();
	Snake* snake = new Snake();
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (snake->Move(c)) {
				break;
			}
		}
		snake->Move();
		snake->Draw();
		Sleep(100);
	}

	_getch();
	endwin();
	return 0;
}
