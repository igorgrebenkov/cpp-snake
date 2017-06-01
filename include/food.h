#pragma once

class Food {
private:
	int y;
	int x;
public:
	Food(int yPos, int xPos) : y(yPos), x(xPos) {};
	int getY() { return y; }
	int getX() { return x; }
};