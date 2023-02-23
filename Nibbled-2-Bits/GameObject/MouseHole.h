#pragma once
#include "Boundary.h"
class MouseHole:public Obstacle
{
private:
	int MouseToExit{ 0 };
public:
	MouseHole(Play::Point2D pos);
	~MouseHole();


};

