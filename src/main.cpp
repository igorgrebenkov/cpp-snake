#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include "curses.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include "snake.h"


WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
int kbhit(void);

int main(int argc, char* argv[]) {
	int snake_x, snake_y;
	int ch;

	initscr();				
	cbreak();				
	curs_set(FALSE);            
	keypad(stdscr, TRUE);		// enable function keys
	nodelay(stdscr, TRUE);      // make getch non-blocking

	snake_y = LINES / 2;
	snake_x = COLS / 2;

	std::shared_ptr<Snake> s = std::make_shared<Snake>(snake_x, snake_y, 20, Direction::UP);  


	for (auto seg : s->getBody()) {
		mvprintw(seg->y, seg->x, "O");
	}

	refresh();
	
	while (ch != KEY_F(1)) {
		for (auto seg : s->getBody()) {
			mvprintw(seg->y, seg->x, "O");
		}
		refresh();

		if (kbhit()) {
			switch (ch = getch()) {
				case KEY_UP:
					s->setDirection(Direction::UP);
					break;
				case KEY_DOWN:
					s->setDirection(Direction::DOWN);
					break;
				case KEY_LEFT:
					s->setDirection(Direction::LEFT);
					break;
				case KEY_RIGHT:
					s->setDirection(Direction::RIGHT);
					break;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		s->moveSnake();
		clear();
	}
	
	endwin();			/* End curses mode */
	return 0;
}


WINDOW *create_newwin(int height, int width, int starty, int startx) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);		/* 0, 0 gives default characters
								 * for the vertical and horizontal lines	*/
	wrefresh(local_win);		/* Show that box */

	return local_win;
}

void destroy_win(WINDOW *local_win) {
	/* box(local_win, ' ', ' '); : This won't produce the desired
	* result of erasing the window. It will leave it's four corners
	* and so an ugly remnant of window.
	*/
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	/* The parameters taken are
	* 1. win: the window on which to operate
	* 2. ls: character to be used for the left side of the window
	* 3. rs: character to be used for the right side of the window
	* 4. ts: character to be used for the top side of the window
	* 5. bs: character to be used for the bottom side of the window
	* 6. tl: character to be used for the top left corner of the window
	* 7. tr: character to be used for the top right corner of the window
	* 8. bl: character to be used for the bottom left corner of the window
	* 9. br: character to be used for the bottom right corner of the window
	*/
	wrefresh(local_win);
	delwin(local_win);
}

int kbhit(void) {
	int ch = getch();

	if (ch != ERR) {
		ungetch(ch);
		return 1;
	}
	else {
		return 0;
	}
}


