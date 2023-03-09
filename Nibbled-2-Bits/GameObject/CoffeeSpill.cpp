#include "pch.h"
#include "CoffeeSpill.h"

CoffeeSpill::CoffeeSpill(Play::Point2D pos) : Obstacle(pos, E_OBJTYPE::E_COFFEESPILL)
{
	spriteName = "coffee_spill";
	m_circleCollider.Init(m_pos, (Play::GetSpriteHeight(spriteName) - 5.0f) * m_scale / 2);
}

void CoffeeSpill::Update()
{
	Obstacle::Render();
	m_circleCollider.DrawBoundingBox();
}