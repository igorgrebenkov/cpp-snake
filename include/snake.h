#pragma once
#include <memory>
#include <vector>
#include "point.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class SnakeSegment : public Point {
private:
	int x;
	int y;
public:
	SnakeSegment(int xPos, int yPos) : Point(yPos, xPos) { };
};

class Snake {
private:
	int length;
	Direction direction;
	std::shared_ptr<SnakeSegment> head;
    std::vector<std::shared_ptr<SnakeSegment>> snakeBody;
public:
	Snake(int x, int y, int len, Direction d);
	std::shared_ptr<SnakeSegment> getHead();
	std::vector<std::shared_ptr<SnakeSegment>> getBody();
	int getLength();
	void setDirection(Direction d);
	void moveSnake();
	void grow(int rate);
	bool canMove(Direction newDirection);
};

