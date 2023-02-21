#include "pch.h"
#include "ConsumableObj.h"
#include "../MainGame.h"
ConsumableObj::ConsumableObj(Play::Point2D pos, E_OBJTYPE type) :GameObject(pos, type)
{

}

ConsumableObj::~ConsumableObj()
{

}

void ConsumableObj::Update()
{
	Render();
}

void ConsumableObj::Render()
{
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale ,0.0f,0.0f },
		{ 0.0f,m_scale ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt, 0);
	m_boxCollider.DrawBoundingBox();
}

BoxCollider& ConsumableObj::GetCollider()
{
	return m_boxCollider;
}
