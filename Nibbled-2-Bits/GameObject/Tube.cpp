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
	while (rot < 0)
	{
		rot += 360;
	}
	while (rot >= 360)
	{
		rot -= 360;
	}
	m_rot += rot;
	OnDirctionChange(rot);
}

void Tube::SetType(E_TUBE_TYPE type)
{
	tube_type = type;
	OnTypeChange();
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
	normal_line.Normalize();
	left_line.Normalize();
	right_line.Normalize();
	inverseNormal_line.Normalize();
}

void Tube::Update()
{
	Render();
	//m_circleCollider.DrawBoundingBox();
}

void Tube::Render()
{
	while (m_rot < 0)
	{
		m_rot += 360;
	}
	while (m_rot >= 360)
	{
		m_rot -= 360;
	}
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale,0.0f,0.0f },
		{ 0.0f,m_scale,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);



	//DrawDebugInfo(Play::cBlue);
	//DrawTubeOpenDir();
}

void Tube::DrawTubeOpenDir()
{
	float line_long = 100;
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
		Play::DrawLine(startPos, endPos, Play::cRed);
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
	tubeToMice.Normalize();

	switch (tube_type)
	{
	case E_TUBE_TYPE::CROSS:
		
		break;
	case E_TUBE_TYPE::ONEWAY:
	{
		float distance = (mice->GetPosition() - m_pos).Length();
		//when degree with the line < 20, cone is 40 dergee, allow to get in
		if (acos(Play::dot(tubeToMice, left_line)) <= Play::DegToRad(20) || acos(Play::dot(tubeToMice, right_line)) <= Play::DegToRad(20))// 30 degree
		{

		}//when mouse totally get in, avoid to be poped out
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
	{
		float distance = (mice->GetPosition() - m_pos).Length();
		//when degree with the line < 20, cone is 40 dergee, allow to get in
		if (acos(Play::dot(tubeToMice, normal_line)) <= Play::DegToRad(10) )
		{
			mouse_cur_dir = 0;
		}
		else if ( acos(Play::dot(tubeToMice, right_line)) <= Play::DegToRad(10))
		{
			mouse_cur_dir = 1;
		}
		else if (distance < 10)//when enter tube center, change direction
		{
			if (mouse_cur_dir == 0)
			{
				mice->SetRotation(m_rot - 90);
			}
			else if (mouse_cur_dir == 1)
			{
				mice->SetRotation(m_rot);
			}
		}
		//when mouse totally get in, avoid to be poped out
		else if (distance < GetCollider().GetRadius())
		{
			//when mice in the tube, if try to go out in wrong direction, back to tube
			if (acos(Play::dot(tubeToMice, normal_line)) <= Play::DegToRad(10) || acos(Play::dot(tubeToMice, right_line)) <= Play::DegToRad(10))
			{
				
			}
			else
			{
				mice->SetPosition(m_pos);
			}
		}
		else
		{
			Play::Vector2D dir = normalize(mice->m_pos - m_pos);
			mice->m_pos = m_pos + GetCollider().GetRadius() * dir + mice->GetCollider().GetRadius() * dir;
		}
	}
		break;
	case E_TUBE_TYPE::THREEWAY:
	{
		float distance = (mice->GetPosition() - m_pos).Length();
		//when degree with the line < 20, cone is 40 dergee, allow to get in
		if (acos(Play::dot(tubeToMice, normal_line)) <= Play::DegToRad(10))// 30 degree
		{
			mouse_cur_dir = 0;
		}
		else if (acos(Play::dot(tubeToMice, right_line)) <= Play::DegToRad(10))
		{
			mouse_cur_dir = 1;
		}
		else if (acos(Play::dot(tubeToMice, left_line)) <= Play::DegToRad(10))
		{
			mouse_cur_dir = 2;
		}
		else if (distance < 10)
		{
			if (mouse_cur_dir == 0)
			{
				mice->SetRotation(m_rot - 90);
			}
			else if (mouse_cur_dir == 1)
			{
				mice->SetRotation(m_rot);
			}
			else if (mouse_cur_dir == 2)
			{
				//mice->SetRotation(m_rot + 90);
			}
		}
		//when mouse totally get in, avoid to pop out
		else if (distance < GetCollider().GetRadius())
		{
			if (acos(Play::dot(tubeToMice, normal_line)) <= Play::DegToRad(10) || acos(Play::dot(tubeToMice, right_line)) <= Play::DegToRad(10) || acos(Play::dot(tubeToMice, left_line)) <= Play::DegToRad(10))
			{

			}
			else
			{
				mice->SetPosition(m_pos);
			}
		}
		else
		{
			Play::Vector2D dir = normalize(mice->m_pos - m_pos);
			mice->m_pos = m_pos + GetCollider().GetRadius() * dir + mice->GetCollider().GetRadius() * dir;
		}
	}
		break;
	default:
		break;
	}
}
