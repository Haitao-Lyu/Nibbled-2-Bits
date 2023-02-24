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
	//m_circleCollider.DrawBoundingBox();
}

void Obstacle::Render()
{
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale,0.0f,0.0f },
		{ 0.0f,m_scale,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);
	
}

BoxCollider& Obstacle::GetBoxCollider()
{
	return m_boxCollider;
}

CircleCollider& Obstacle::GetCollider()
{
	return m_circleCollider;
}

