#pragma once
#include "Obstacle.h"

class StickySpill:public Obstacle
{

public:
	StickySpill(Play::Point2D pos);

	void Update() override;
};