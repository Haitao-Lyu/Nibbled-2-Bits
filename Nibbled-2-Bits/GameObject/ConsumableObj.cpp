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
	m_boxCollider.DrawBoundingBox();
	m_circleCollider.DrawBoundingBox();
}

void ConsumableObj::Render()
{
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale ,0.0f,0.0f },
		{ 0.0f,m_scale ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);
}

void ConsumableObj::SetIsConsumed(bool value)
{
	isConsumed = value;
}

BoxCollider& ConsumableObj::GetBoxCollider()
{
	return m_boxCollider;
}

CircleCollider& ConsumableObj::GetCollider()
{
	return m_circleCollider;
}
