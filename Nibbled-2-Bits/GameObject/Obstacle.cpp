#include "pch.h"
#include "Obstacle.h"
#include "../MainGame.h"
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

void Obstacle::Render()
{
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ 1.0f ,0.0f,0.0f },
		{ 0.0f,1.0f ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt, 0);
	
}
