#include <memory>
#include <chrono>
#include <thread>
#include <iostream>
#include "curses.h"
#include "snake.h"
#include "food.h"
#include "window.h"
#include "game.h"

Game::Game(int snakeStartY, int snakeStartX, int snakeLength) : score(0), delay(INITIAL_DELAY) {
	scoreBoard = std::make_shared<Window>(BOARD_Y_OFFSET, COLS, 0, 0);
	gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);
	snake = std::make_shared<Snake>(snakeStartX, snakeStartY, SNAKE_START_LENGTH, Direction::UP);
	printScoreBoard();
	printSnake();
	isFood = false;
	isGameOver = false;
	delay = INITIAL_DELAY;
}

void Game::play() {
	while (ch != KEY_F(1) && !isGameOver) {
		if (isWallCollision() || isSnakeCollision()) {
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

void Game::printScoreBoard() {
	mvwprintw(scoreBoard->getWindow(), 1, COLS / 2, "Score: %d", score);
}

void Game::printSnake() {
	for (auto seg : snake->getBody()) {
		mvwprintw(gameBoard->getWindow(), seg->getY(), seg->getX(), "O");
	}
}

void Game::printFood() {
	mvwprintw(gameBoard->getWindow(), food->getY(), food->getX(), "@");
}

void Game::clearFood() {
	mvwprintw(gameBoard->getWindow(), food->getY(), food->getX(), " ");
}

void Game::makeFood() {
	srand(time(NULL));
	int foodY = rand() % (LINES - F_MAX_Y_OFFSET) + (F_MIN_Y);
	int foodX = rand() % (COLS - F_MAX_X_OFFSET) + (F_MIN_X);
	food = std::make_shared<Food>(foodY, foodX);
}

bool Game::ateFood() {
	int snakeHeadX = snake->getHead()->getX();
	int snakeHeadY = snake->getHead()->getY();
	int foodX = food->getX();
	int foodY = food->getY();

	return snakeHeadX == foodX && snakeHeadY == foodY;
}

bool Game::isWallCollision() {
	int snakeHeadX = snake->getHead()->getX();
	int snakeHeadY = snake->getHead()->getY();

	if (snakeHeadY == 0 || snakeHeadY == (LINES - BOARD_Y_OFFSET - 1) ||
		snakeHeadX == 0 || snakeHeadX == COLS - 1) {
		return true;
	}
	return false;
}

bool Game::isSnakeCollision() {
	if (snake->getLength() > 1) {
		int snakeHeadX = snake->getHead()->getX();
		int snakeHeadY = snake->getHead()->getY();

		for (int i = 1; i < snake->getBody().size(); i++) {
			int segX = snake->getBody().at(i)->getX();
			int segY = snake->getBody().at(i)->getY();

			if (snakeHeadX == segX && snakeHeadY == segY) {
				std::cout << "x(" << i << "): " << snakeHeadX << ",y(" << i << "): " << snakeHeadY << " " << std::endl;
				std::cout << "x(" << i << "): " << segX << ",y(" << i << "): " << segY << " " << std::endl;
				return true;
			}
		}
	}
	return false;
}

void Game::gameOver() {
	// Redraw gameBoard to show Snake head's final position on game over
	gameBoard = std::make_shared<Window>(LINES - BOARD_Y_OFFSET, COLS, BOARD_Y_OFFSET, 0);
	printSnake();
	wrefresh(gameBoard->getWindow());

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

void Game::reset() {
	snake = std::make_shared<Snake>(COLS / 2, LINES / 2, SNAKE_START_LENGTH, Direction::UP);
	score = 0;
	delay = INITIAL_DELAY;
	isFood = false;
}

void Game::checkInput() {
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

int Game::kbhit(void) {
	int ch = getch();

	if (ch != ERR) {
		ungetch(ch);
		return 1;
	}
	else {
		return 0;
	}
}