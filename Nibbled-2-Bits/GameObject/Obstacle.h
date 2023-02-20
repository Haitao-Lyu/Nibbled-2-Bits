#pragma once
#include "GameObject.h"

//not all penguien need to be a bird
class Obstacle:public GameObject
{
private:

public:
	Obstacle(Play::Point2D pos,E_OBJTYPE type);
	~Obstacle();

	virtual void Update() override;
};

