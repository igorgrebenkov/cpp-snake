/**
*	point.h
*	A simple point class.
*
*	Author: Igor Grebenkov
*/

#pragma once

class Point {
protected:
	int y;
	int x;
public:
	Point(int yPos, int xPos) : y(yPos), x(xPos) {};
	int getY() { return y; }
	int getX() { return x; }
};