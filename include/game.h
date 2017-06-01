#pragma once

const int BOARD_Y_OFFSET = 3;
const int F_MIN_Y = 2;
const int F_MAX_Y_OFFSET = 6;
const int F_MIN_X = 2;
const int F_MAX_X_OFFSET = 4;
const int INITIAL_DELAY = 50;
const int DELAY_REDUCE = 3;
const int SNAKE_GROWTH_RATE = 5;	
const int SNAKE_START_LENGTH = 1;




class Game {
private:
	int ch;
	int score;
	int delay;
	bool isFood;
	bool isGameOver;
	std::shared_ptr<Window> scoreBoard;
	std::shared_ptr<Window> gameBoard;
	std::shared_ptr<Snake> snake; 
	std::shared_ptr<Food> food;

public:
	Game(int snakeStartY, int snakeStartX, int snakeLength) : score(0), delay(INITIAL_DELAY) {
		scoreBoard = std::make_shared<Window>(BOARD_Y_OFFSET, COLS, 0, 0);
		gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);
		snake = std::make_shared<Snake>(snakeStartX, snakeStartY, SNAKE_START_LENGTH, Direction::UP);
		printScoreBoard();
		printSnake();
		isFood = false;
		isGameOver = false;
	}

	void play() {
		while (ch != KEY_F(1) && !isGameOver) {
			if (isWallCollision()) {
				gameOver();
			}

			scoreBoard = std::make_shared<Window>(BOARD_Y_OFFSET, COLS, 0, 0);
			gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);

			if (!isFood) {
				makeFood();
				isFood = true;
			}

			if (ateFood()) {
				clearFood();
				isFood = false;
				snake->grow(SNAKE_GROWTH_RATE);
				delay -= DELAY_REDUCE;
				score++;
			}

			printSnake();
			printFood();
			printScoreBoard();


			checkInput();
			snake->moveSnake();

			wrefresh(scoreBoard->getWindow());
			wrefresh(gameBoard->getWindow());
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

	bool isWallCollision() {
		int snakeHeadX = snake->getHead()->getX();
		int snakeHeadY = snake->getHead()->getY();

		if (snakeHeadY == 0 || snakeHeadY == (LINES - BOARD_Y_OFFSET) ||
			snakeHeadX == 0 || snakeHeadX == COLS) {
			return true;
		} 
		return false;
	}

	void gameOver() {
		int height = 10;
		int width = 60;

		int maxBoardY;
		int maxBoardX;
		getmaxyx(gameBoard->getWindow(), maxBoardY, maxBoardX);

		int startY = (maxBoardY - height) / 2;
		int startX = (maxBoardX - width) / 2;

		std::shared_ptr<Window> w = std::make_shared<Window>(height, width, startY, startX);
		
		int maxY;
		int maxX;
		getmaxyx(w->getWindow(), maxY, maxX);

		char str1[] = "Game Over!";
		char str2[] = "Press p to play again. Any other key to quit.";

		while (1) {
			
			mvwprintw(w->getWindow(), (maxY / 2) - 2, (maxX - strlen(str1)) / 2, "%s", str1);
			mvwprintw(w->getWindow(), (maxY / 2) + 1, (maxX - strlen(str2)) / 2, "%s", str2);
			wrefresh(w->getWindow());

			if (kbhit()) {
				if ((ch = getch()) == 'p') {
					reset();
				}
				else {
					isGameOver = true;
				}
				break;
			}
		}
	}

	void reset() {
		snake = std::make_shared<Snake>(COLS / 2, LINES / 2, SNAKE_START_LENGTH, Direction::UP);
		score = 0;
		delay = INITIAL_DELAY;
		isFood = false;
	}

	void checkInput() {
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