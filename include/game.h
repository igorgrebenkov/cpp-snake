/**
*	game.h
*	Contains the game objects and logic. 
*
*	Author: Igor Grebenkov
*/
#pragma once
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>
#include "curses.h"
#include "snake.h"
#include "food.h"
#include "window.h"

const int BOARD_Y_OFFSET = 3;
const int F_MIN_Y = 2;
const int F_MAX_Y_OFFSET = 6;
const int F_MIN_X = 2;
const int F_MAX_X_OFFSET = 4;
const int INITIAL_DELAY = 50;
const int DELAY_REDUCE = 1;
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
	void printScoreBoard();
	void printSnake();
	void printFood();
	void clearFood();
	void makeFood();
	bool ateFood();
	bool isWallCollision();
	bool isSnakeCollision();
	void gameOver();
	void gameOverMusic();
	void beep();
	void reset();
	void checkInput();
	int kbhit(void);
};