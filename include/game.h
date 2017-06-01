#pragma once

#include <iostream>
#include "curses.h"
#include "window.h"
#include "snake.h"

const int BOARD_Y_OFFSET = 3;

class Game {
public:
	int score;
	std::shared_ptr<Window> scoreBoard;
	std::shared_ptr<Window> gameBoard;
	std::shared_ptr<Snake> snake; 

	Game(int snakeStartY, int snakeStartX, int snakeLength) : score(0) {
		scoreBoard = std::make_shared<Window>(BOARD_Y_OFFSET, COLS, 0, 0);
		mvwprintw(scoreBoard->getWindow(), 1, COLS / 2, "Score: %d", score);
		wrefresh(scoreBoard->getWindow());

		gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);
		snake = std::make_shared<Snake>(snakeStartX, snakeStartY, snakeLength, Direction::UP);

		for (auto seg : snake->getBody()) {
			mvwprintw(gameBoard->getWindow(), seg->y, seg->x, "O");
		}
		wrefresh(gameBoard->getWindow());
	}

	void play(int ch) {
		while (ch != KEY_F(1)) {
			scoreBoard = std::make_shared<Window>(BOARD_Y_OFFSET, COLS, 0, 0);
			mvwprintw(scoreBoard->getWindow(), 1, COLS / 2, "Score: %d", score);
			wrefresh(scoreBoard->getWindow());

			gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);

			for (auto seg : snake->getBody()) {
				mvwprintw(gameBoard->getWindow(), seg->y, seg->x, "O");
			}
			wrefresh(gameBoard->getWindow());

			if (kbhit()) {
				switch (ch = getch()) {
					case KEY_UP:
						if (snake->canMove(Direction::UP)) {
							snake->setDirection(Direction::UP);
						}
						break;
					case KEY_DOWN:
						if (snake->canMove(Direction::DOWN)) {
							snake->setDirection(Direction::DOWN);
						}
						break;
					case KEY_LEFT:
						if (snake->canMove(Direction::LEFT)) {
							snake->setDirection(Direction::LEFT);
						}
						break;
					case KEY_RIGHT:
						if (snake->canMove(Direction::RIGHT)) {
							snake->setDirection(Direction::RIGHT);
						}
						break;
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			snake->moveSnake();
		}
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
};