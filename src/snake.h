#pragma once
#include <vector>

enum class Direction { UP, DOWN, LEFT, RIGHT };

class SnakeSegment {
public:
	int x;
	int y;

	SnakeSegment() = default;
	SnakeSegment(int x_coord, int y_coord) : x(x_coord), y(y_coord) {};
};

class Snake {
public:
	int length;
	Direction direction;
	std::shared_ptr<SnakeSegment> head;
	std::vector<std::shared_ptr<SnakeSegment>> snakeBody;

	Snake(int x, int y, int len, Direction d) : length(len), direction(d) {

		snakeBody.push_back(std::make_shared<SnakeSegment>(x, y));
		head = snakeBody.front();

		for (int i = 0; i < length - 1; i++) {
			x++;
			snakeBody.push_back(std::make_shared<SnakeSegment>(x, y));
		}

	}

	std::vector<std::shared_ptr<SnakeSegment>> getBody() {
		return snakeBody;
	}

	void setDirection(Direction d) { direction = d; };
	void moveSnake() {
		switch (direction) {
			case Direction::UP:
				head = std::make_shared<SnakeSegment>(head->x, head->y - 1);
				break;
			case Direction::DOWN:
				head = std::make_shared<SnakeSegment>(head->x, head->y + 1);
				break;
			case Direction::RIGHT:
				head = std::make_shared<SnakeSegment>(head->x + 1, head->y);
				break;
			case Direction::LEFT:
				head = std::make_shared<SnakeSegment>(head->x - 1, head->y);
				break;
		}
		snakeBody.insert(snakeBody.begin(), head);
		snakeBody.pop_back();
	}
};

