
#include "snake.h"

Snake:: Snake(int x, int y, int len, Direction d) : length(len), direction(d) {

	snakeBody.push_back(std::make_shared<SnakeSegment>(x, y));
	head = snakeBody.front();

	for (int i = 0; i < length - 1; i++) {
		x++;
		snakeBody.push_back(std::make_shared<SnakeSegment>(x, y));
	}
}

std::shared_ptr<SnakeSegment> Snake::getHead() {
	return head;
}

std::vector<std::shared_ptr<SnakeSegment>> Snake::getBody() {
	return snakeBody;
}

int Snake::getLength() {
	return length;
}

void Snake::setDirection(Direction d) { 
	direction = d; 
}

void Snake::moveSnake() {
	switch (direction) {
		case Direction::UP:
			head = std::make_shared<SnakeSegment>(head->getX(), head->getY() - 1);
			break;
		case Direction::DOWN:
			head = std::make_shared<SnakeSegment>(head->getX(), head->getY() + 1);
			break;
		case Direction::RIGHT:
			head = std::make_shared<SnakeSegment>(head->getX() + 1, head->getY());
			break;
		case Direction::LEFT:
			head = std::make_shared<SnakeSegment>(head->getX() - 1, head->getY());
			break;
	}

	snakeBody.insert(snakeBody.begin(), head);
	snakeBody.pop_back();
}

void Snake::grow(int rate) {
	std::shared_ptr<SnakeSegment> tail = snakeBody.back();

	for (int i = 0; i < rate; i++) {
		switch (direction) {
			case Direction::UP:
				snakeBody.push_back(std::make_shared<SnakeSegment>(tail->getX(), tail->getY() + i));
				break;
			case Direction::DOWN:
				snakeBody.push_back(std::make_shared<SnakeSegment>(tail->getX(), tail->getY() - i));
				break;
			case Direction::RIGHT:
				snakeBody.push_back(std::make_shared<SnakeSegment>(tail->getX() - i, tail->getY()));
				break;
			case Direction::LEFT:
				snakeBody.push_back(std::make_shared<SnakeSegment>(tail->getX() + i, tail->getY()));
				break;
		}
	}
	length += rate;
}

bool Snake::canMove(Direction newDirection) {
	if (length > 1) {
		std::shared_ptr<SnakeSegment> afterHead = snakeBody.at(1);
		switch (newDirection) {
			case Direction::UP:
				if ((head->getY() - 1) == afterHead->getY()) {
					return false;
				}
				break;
			case Direction::DOWN:
				if ((head->getY() + 1) == afterHead->getY()) {
					return false;
				}
				break;
			case Direction::RIGHT:
				if ((head->getX() + 1) == afterHead->getX()) {
					return false;
				}
				break;
			case Direction::LEFT:
				if ((head->getX() - 1) == afterHead->getX()) {
					return false;
				}
				break;
		}
	}
	return true;
}