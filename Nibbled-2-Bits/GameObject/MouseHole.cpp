#include "pch.h"
#include "MouseHole.h"
#include "../Manager/GameObjectMgr.h"
const char* mouseHoleName_b = "mouse_hole_bottom";
const char* mouseHoleName_l = "mouse_hole_left";
const char* mouseHoleName_r = "mouse_hole_right";
const char* mouseHoleName_t = "mouse_hole_top";

const char* white_mouseHoleName_b = "mouse_hole_with_back_bottom";
const char* white_mouseHoleName_l = "mouse_hole_with_back_left";
const char* white_mouseHoleName_r = "mouse_hole_with_back_right";
const char* white_mouseHoleName_t = "mouse_hole_with_back_top";

MouseHole::MouseHole(Play::Point2D pos, E_MOUSEHOLE_DIR dir):Obstacle(pos,E_OBJTYPE::E_MOUSEHOLE)
{
	SetDirection(dir);
	m_circleCollider.Init(pos, (Play::GetSpriteHeight(spriteName) - 3.0f) / 2 * m_scale);
}

MouseHole::~MouseHole()
{

}

void MouseHole::SetDirection(E_MOUSEHOLE_DIR dir)
{
	switch (m_color_type)
	{
	case E_BOUNDARY_COLOR::WHITE:
	{
		switch (dir)
		{
		case E_MOUSEHOLE_DIR::TOP:
			spriteName = white_mouseHoleName_t;
			break;
		case E_MOUSEHOLE_DIR::LEFT:
			spriteName = white_mouseHoleName_l;
			break;
		case E_MOUSEHOLE_DIR::BOTTOM:
			spriteName = white_mouseHoleName_b;
			break;
		case E_MOUSEHOLE_DIR::RIGHT:
			spriteName = white_mouseHoleName_r;
			break;
		default:
			break;
		}
	}
		break;
	case E_BOUNDARY_COLOR::WOOD:
	{
		switch (dir)
		{
		case E_MOUSEHOLE_DIR::TOP:
			spriteName = mouseHoleName_t;
			break;
		case E_MOUSEHOLE_DIR::LEFT:
			spriteName = mouseHoleName_l;
			break;
		case E_MOUSEHOLE_DIR::BOTTOM:
			spriteName = mouseHoleName_b;
			break;
		case E_MOUSEHOLE_DIR::RIGHT:
			spriteName = mouseHoleName_r;
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}

}

void MouseHole::OnMouseIn(Mouse &mouse)
{

	switch (m_type)
	{
	case E_MOUSEHOLE_TYPE::ENTRY:
	{
		Play::Vector2D dir = normalize(mouse.m_pos - m_pos);
		mouse.m_pos = m_pos + m_circleCollider.GetRadius() * dir + mouse.GetCollider().GetRadius() * dir;
		break;
	}
	case E_MOUSEHOLE_TYPE::EXIT:
		GameObjectMgr::RemoveGameObject(mouse);
		break;
	default:
		break;
	}
}

void MouseHole::SetType(E_MOUSEHOLE_TYPE _type)
{
	m_type = _type;
}
