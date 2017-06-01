#pragma once

const int BOARD_Y_OFFSET = 3;

class Game {
private:
	int score;
	std::shared_ptr<Window> scoreBoard;
	std::shared_ptr<Window> gameBoard;
	std::shared_ptr<Snake> snake; 
	std::shared_ptr<Food> food;

public:
	Game(int snakeStartY, int snakeStartX, int snakeLength) : score(0) {
		scoreBoard = std::make_shared<Window>(BOARD_Y_OFFSET, COLS, 0, 0);
		gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);
		snake = std::make_shared<Snake>(snakeStartX, snakeStartY, snakeLength, Direction::UP);
		printScoreBoard();
		printSnake();
	}

	void play() {
		int ch;
		
		while (ch != KEY_F(1)) {
			scoreBoard = std::make_shared<Window>(BOARD_Y_OFFSET, COLS, 0, 0);
			gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);

			printScoreBoard();
			printSnake();

			checkInput(ch);

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			snake->moveSnake();
		}
	}

private:
	void checkInput(int& ch) {
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
	}

	void printSnake() {
		for (auto seg : snake->getBody()) {
			mvwprintw(gameBoard->getWindow(), seg->y, seg->x, "O");
		}
		wrefresh(gameBoard->getWindow());
	}

	void printScoreBoard() {
		mvwprintw(scoreBoard->getWindow(), 1, COLS / 2, "Score: %d", score);
		wrefresh(scoreBoard->getWindow());
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