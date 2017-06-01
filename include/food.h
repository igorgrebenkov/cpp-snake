#pragma once
#include "Point.h"

class Food : public Point { 
public:
	Food(int yPos, int xPos) : Point(yPos, xPos) { };
};