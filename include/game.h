/**
*	game.h
*	Contains the game objects and logic. 
*
*	Author: Igor Grebenkov
*/
#pragma once

#ifdef _WIN32
	#include <windows.h> 
	#include "pdcurses.h"
#elif __linux__
	#include "curses.h"
#endif

#include <memory>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstring>
#include "snake.h"
#include "food.h"
#include "window.h"

const int BOARD_Y_OFFSET = 3;
const int F_MIN_Y = 2;
const int F_MAX_Y_OFFSET = 6;
const int F_MIN_X = 2;
const int F_MAX_X_OFFSET = 4;
const int INITIAL_DELAY = 120;
const int DELAY_REDUCE = 2;
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
	Game(int snakeStartY, int snakeStartX, int snakeLength); 
	void play();
private:
	void createWindows();
	void printScoreBoard();
	void printSnake();
	void printFood();
	void clearFood();
	bool makeFood();
	bool ateFood();
	bool isWallCollision();
	bool isSnakeCollision();
	void gameOver();
	void gameOverMusic();
	void reset();
	bool checkInput();
	int kbhit(void);
};