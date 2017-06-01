#pragma once

const int BOARD_Y_OFFSET = 3;
const int F_MIN_Y = 2;
const int F_MAX_Y_OFFSET = 6;
const int F_MIN_X = 2;
const int F_MAX_X_OFFSET = 4;
const int INITIAL_DELAY = 20;
const int SNAKE_GROWTH_RATE = 5;


class Game {
private:
	int score;
	int delay;
	bool isFood;
	std::shared_ptr<Window> scoreBoard;
	std::shared_ptr<Window> gameBoard;
	std::shared_ptr<Snake> snake; 
	std::shared_ptr<Food> food;

public:
	Game(int snakeStartY, int snakeStartX, int snakeLength) : score(0), delay(INITIAL_DELAY) {
		scoreBoard = std::make_shared<Window>(BOARD_Y_OFFSET, COLS, 0, 0);
		gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);
		snake = std::make_shared<Snake>(snakeStartX, snakeStartY, snakeLength, Direction::UP);
		printScoreBoard();
		printSnake();
		isFood = false;
	}

	void play() {
		int ch;
		scoreBoard = std::make_shared<Window>(BOARD_Y_OFFSET, COLS, 0, 0);
		gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);

		while (ch != KEY_F(1)) {

			if (!isFood) {
				makeFood();
				isFood = true;
			}

			if (ateFood()) {
				clearFood();
				isFood = false;
				snake->grow(SNAKE_GROWTH_RATE);
				delay -= 10;
				score++;
			}

			printSnake();
			printFood();
			printScoreBoard();

			checkInput(ch);
			snake->moveSnake();

			wrefresh(gameBoard->getWindow());
			wrefresh(scoreBoard->getWindow());

			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
	}

private:
	void printScoreBoard() {
		mvwprintw(scoreBoard->getWindow(), 1, COLS / 2, "Score: %d", score);
	}

	void printSnake() {
		for (auto seg : snake->getBody()) {
			mvwprintw(gameBoard->getWindow(), seg->getY(), seg->getX(), "O");
		}
	}

	void printFood() {
		mvwprintw(gameBoard->getWindow(), food->getY(), food->getX(), "@");
	}

	void clearFood() {
		mvwprintw(gameBoard->getWindow(), food->getY(), food->getX(), " ");
	}

	void makeFood() {
		srand(time(NULL));
		int foodY = rand() % (LINES - F_MAX_Y_OFFSET) + (F_MIN_Y);
		int foodX = rand() % (COLS - F_MAX_X_OFFSET) + (F_MIN_X);
		food = std::make_shared<Food>(foodY, foodX);
	}

	bool ateFood() {
		int snakeHeadX = snake->getHead()->getX();
		int snakeHeadY = snake->getHead()->getY();
		int foodX = food->getX();
		int foodY = food->getY();

		return snakeHeadX == foodX && snakeHeadY == foodY;
	}

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