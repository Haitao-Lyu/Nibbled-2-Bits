#include "pch.h"
#include "Tube.h"
#include "../MainGame.h"
const char* tube_cross_name = "iron_tube_cross"	;
const char* tube_one_name = "iron_tube_one_way"	;
const char* tube_three_name = "iron_tube_three_way";
const char* tube_two_name = "iron_tube_two_way";

Tube::Tube(Play::Point2D pos, E_TUBE_TYPE type):Obstacle(pos,E_OBJTYPE::E_TUBE)
{
	tube_type = type;
	OnTypeChange();
	m_scale = 0.5;
	m_circleCollider.Init(m_pos,Play::GetSpriteWidth(spriteName) * m_scale);
}

void Tube::OnTypeChange()
{
	switch (tube_type)
	{
	case E_TUBE_TYPE::CROSS:
		spriteName = tube_cross_name;
		break;
	case E_TUBE_TYPE::ONEWAY:
		spriteName = tube_one_name;
		break;
	case E_TUBE_TYPE::TWOWAY:
		spriteName = tube_two_name;
		break;
	case E_TUBE_TYPE::THREEWAY:
		spriteName = tube_three_name;
		break;
	default:
		break;
	}
}

void Tube::Update()
{

	Render();
	m_circleCollider.DrawBoundingBox();
}

void Tube::Render()
{
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale,0.0f,0.0f },
		{ 0.0f,m_scale,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);
}
