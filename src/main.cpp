/**
*	main.cpp
*	Contains main, which initializes curses and starts a game.
*
*	Author: Igor Grebenkov
*/

#include <memory>
#include "game.h"

int main(int argc, char* argv[]) {
	initscr();				
	cbreak();				
	curs_set(FALSE);            
	keypad(stdscr, TRUE);		
	nodelay(stdscr, TRUE);      // make getch non-blocking
	noecho();
	start_color();

	const int SNAKE_START_Y = (LINES / 2) + 10;
	const int SNAKE_START_X = COLS / 2;
	
	std::shared_ptr<Game> g = std::make_shared<Game>(SNAKE_START_Y,
		SNAKE_START_X,
		SNAKE_START_LENGTH);
	
	g->play();
	werase(stdscr);
	
	endwin();			/* End curses mode */
	return 0;
}




