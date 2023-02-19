#include "Obstacle.h"

Obstacle::Obstacle(Play::Point2D pos, E_TILE_COLOR color) :GameObject(pos)
{
	m_color = color;
}


Obstacle::~Obstacle()
{
}

void Obstacle::Update()
{

}
