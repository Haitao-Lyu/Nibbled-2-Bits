#pragma once

#include "Obstacle.h"
class CoffeeSpill :public Obstacle
{


public:
	CoffeeSpill(Play::Point2D pos);

	void Update() override;
};