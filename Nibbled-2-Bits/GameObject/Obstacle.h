#pragma once
#include "GameObject.h"

//not all penguien need to be a bird
//which way is better perpare base class ahead or create it when shared feature show up
class Obstacle:public GameObject
{
private:

public:
	Obstacle(Play::Point2D pos,E_OBJTYPE type);
	~Obstacle();

	virtual void Update() override;
	virtual void Render() override;
};

