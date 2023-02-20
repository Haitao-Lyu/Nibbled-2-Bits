#pragma once
#include "GameObject.h"



class Obstacle:public GameObject
{
private:

public:
	Obstacle(Play::Point2D pos,E_OBJTYPE type);
	~Obstacle();

	virtual void Update() override;
};

