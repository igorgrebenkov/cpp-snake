/**
*	food.h
*	Represents a piece of food. Subclass of Point.
*
*	Author: Igor Grebenkov
*/

#pragma once
#include "Point.h"

class Food : public Point { 
public:
	Food(int yPos, int xPos) : Point(yPos, xPos) { };
};