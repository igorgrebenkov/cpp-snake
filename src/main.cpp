#include <iostream>
#include <string>
#include <vector>
#include "curses.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "snake.h"
#include "window.h"
#include "game.h"



int main(int argc, char* argv[]) {

	initscr();				
	cbreak();				
	curs_set(FALSE);            
	keypad(stdscr, TRUE);		// enable function keys
	nodelay(stdscr, TRUE);      // make getch non-blocking

	const int SNAKE_START_Y = LINES / 2;
	const int SNAKE_START_X = COLS / 2;
	const int SNAKE_START_LENGTH = 1;
	
	int ch;

	std::shared_ptr<Game> g = std::make_shared<Game>(SNAKE_START_Y,
		SNAKE_START_X,
		SNAKE_START_LENGTH);
	
	g->play(ch);
	
	endwin();			/* End curses mode */
	return 0;
}




