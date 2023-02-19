#include "Obstacle.h"

Obstacle::Obstacle(Play::Point2D pos, E_OBJTYPE type):GameObject(pos, type)
{
	
}


Obstacle::~Obstacle()
{
}

void Obstacle::Update()
{
	Render();
}
