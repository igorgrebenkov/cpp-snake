/**
*	window.h
*	The class Window creates a curses window.
*
*	Author: Igor Grebenkov
*/

#pragma once
const int BORDER_STYLE = 0;

class Window {
public:
	WINDOW* window;
	Window(int height, int width, int y, int x) {
		window = newwin(height, width, y, x);
		wattron(window, COLOR_PAIR(2));
		box(window, BORDER_STYLE, BORDER_STYLE);		
		wattroff(window, COLOR_PAIR(2));
		wrefresh(window);		
	}

	WINDOW* getWindow() {
		return window;
	}

	~Window() {
		delwin(window);
	}
};