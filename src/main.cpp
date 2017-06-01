/**
*	main.cpp
*	Contains main, which initializes curses and starts a game.
*
*	Author: Igor Grebenkov
*/

#include <vector>
#include <memory>

#include "curses.h"
#include "game.h"

int main(int argc, char* argv[]) {
	initscr();				
	cbreak();				
	curs_set(FALSE);            
	keypad(stdscr, TRUE);		// enable function keys
	nodelay(stdscr, TRUE);      // make getch non-blocking
	noecho();

	const int SNAKE_START_Y = LINES / 2;
	const int SNAKE_START_X = COLS / 2;
	
	std::shared_ptr<Game> g = std::make_shared<Game>(SNAKE_START_Y,
		SNAKE_START_X,
		SNAKE_START_LENGTH);
	
	g->play();
	werase(stdscr);
	
	endwin();			/* End curses mode */
	return 0;
}




