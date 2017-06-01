#pragma once
#include <memory>
#include <vector>
enum class Direction { UP, DOWN, LEFT, RIGHT };

class SnakeSegment {
private:
	int x;
	int y;
public:
	SnakeSegment() = default;
	SnakeSegment(int x_coord, int y_coord) : x(x_coord), y(y_coord) {};
	int getX() { return x; }
	int getY() { return y; }
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

