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
	m_circleCollider.Init(m_pos,Play::GetSpriteWidth(spriteName)/2 * m_scale);
	m_boxCollider.Init(Play::GetSpriteWidth(spriteName) * m_scale, Play::GetSpriteHeight(spriteName) * m_scale, m_pos, this);

	normal_line = (m_boxCollider.lt - m_boxCollider.rt).Perpendicular();
	normal_line.Normalize();
	right_line = normal_line.Perpendicular();
	left_line = -right_line;
	inverseNormal_line = -normal_line;
}

void Tube::Rotate(float rot)
{
	m_rot += rot;
	OnDirctionChange(rot);
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

void Tube::OnDirctionChange(float rot)
{
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(rot));
	normal_line = rotMt.Transform(normal_line);
	right_line = normal_line.Perpendicular();
	left_line = -right_line;
	inverseNormal_line = -normal_line;
}

void Tube::Update()
{
	Render();
	m_circleCollider.DrawBoundingBox();
}

void Tube::Render()
{
	while (m_rot < 0)
	{
		m_rot >= 360;
	}
	while (m_rot > 360)
	{
		m_rot -= 360;
	}
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale,0.0f,0.0f },
		{ 0.0f,m_scale,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);



	DrawDebugInfo(Play::cBlue);
	DrawTubeOpenDir();
}

void Tube::DrawTubeOpenDir()
{
	int line_long = 100;
	Play::Point2D startPos = m_pos;
	Play::Point2D endPos = startPos + normal_line * line_long;

	Play::Vector2D normalDir = endPos - startPos;
	normalDir.Normalize();

	switch (tube_type)
	{
	case E_TUBE_TYPE::CROSS:

		break;
	case E_TUBE_TYPE::ONEWAY:
		Play::DrawLine(startPos, startPos + right_line * line_long, Play::cGreen);
		Play::DrawLine(startPos, startPos + left_line * line_long, Play::cGreen);
		break;
	case E_TUBE_TYPE::TWOWAY:
		Play::DrawLine(startPos, endPos, Play::cGreen);
		Play::DrawLine(startPos, startPos + right_line * line_long, Play::cGreen);
		break;
	case E_TUBE_TYPE::THREEWAY:
		Play::DrawLine(startPos, endPos, Play::cGreen);
		Play::DrawLine(startPos, startPos + right_line * line_long, Play::cGreen);
		Play::DrawLine(startPos, startPos + left_line * line_long, Play::cGreen);
		break;
	default:
		break;
	}
}

void Tube::CollideMouse(Mouse* mice)
{
	//move obj backward based on the distance and direction between two obj


	Play::Vector2D tubeToMice = mice->m_pos - m_pos;

	switch (tube_type)
	{
	case E_TUBE_TYPE::CROSS:
		
		break;
	case E_TUBE_TYPE::ONEWAY:
	{
		tubeToMice.Normalize();
		left_line.Normalize();
		right_line.Normalize();
		float distance = (mice->GetPosition() - m_pos).Length();
		//allow to get in
		if (acos(Play::dot(tubeToMice, left_line)) <= Play::DegToRad(20) || acos(Play::dot(tubeToMice, right_line)) <= Play::DegToRad(20))// 30 degree
		{

		}
		else if (distance < GetCollider().GetRadius())
		{

		}
		else
		{
			Play::Vector2D dir = normalize(mice->m_pos - m_pos);
			mice->m_pos = m_pos + GetCollider().GetRadius() * dir + mice->GetCollider().GetRadius() * dir;
		}
		//TODO: USE THE REST LINE TO CHECK INSIDE CANT GET OUT
	}

		break;
	case E_TUBE_TYPE::TWOWAY:

		break;
	case E_TUBE_TYPE::THREEWAY:

		break;
	default:
		break;
	}
}
