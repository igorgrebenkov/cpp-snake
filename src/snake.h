#pragma once
enum class Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
	public:
		int x;
		int y;
		Direction direction;

		Snake() = default;
		Snake(int x_coord, int y_coord, Direction d) : x(x_coord), y(y_coord) { direction = d; };
		void setDirection(Direction d) { direction = d; };
		void moveSnake() {
			switch (direction) {
				case Direction::UP:
					y--;
					break;
				case Direction::DOWN:
					y++;
					break;
				case Direction::RIGHT:
					x++;
					break;
				case Direction::LEFT:
					x--;
					break;
			}
		}
};