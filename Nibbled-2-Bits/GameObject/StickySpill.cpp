#include "pch.h"
#include "StickySpill.h"

StickySpill::StickySpill(Play::Point2D pos): Obstacle(pos, E_OBJTYPE::E_STICKYSPILL)
{
	spriteName = "StickySpill";
	m_circleCollider.Init(m_pos, (Play::GetSpriteHeight(spriteName) - 5.0f) * m_scale / 2);
}

void StickySpill::Update()
{
	Obstacle::Render();
	//m_circleCollider.DrawBoundingBox();
}


