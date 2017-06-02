/**
*	window.h
*	The class Window creates a curses window.
*
*	Author: Igor Grebenkov
*/

#pragma once

class Window {
public:
	WINDOW* window;
	Window(int height, int width, int y, int x) {
		window = newwin(height, width, y, x);
		wattron(window, COLOR_PAIR(2));
		box(window, 0, 0);		/* 0, 0 gives default characters
									* for the vertical and horizontal lines	*/
		wattroff(window, COLOR_PAIR(2));
		wrefresh(window);		
	}
	WINDOW* getWindow() {
		return window;
	}
};