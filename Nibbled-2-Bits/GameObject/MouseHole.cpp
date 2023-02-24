#include "pch.h"
#include "MouseHole.h"
#include "GameObjectMgr.h"
const char* mouseHoleName_b = "mouse_hole_bottom";
const char* mouseHoleName_l = "mouse_hole_left";
const char* mouseHoleName_r = "mouse_hole_right";
const char* mouseHoleName_t = "mouse_hole_top";

MouseHole::MouseHole(Play::Point2D pos, E_MOUSEHOLE_DIR dir):Obstacle(pos,E_OBJTYPE::E_MOUSEHOLE)
{
	SetScale(1.25f);

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
	m_circleCollider.Init(pos, Play::GetSpriteHeight(spriteName) / 2 + 5.0f * m_scale);
}

MouseHole::~MouseHole()
{

}

void MouseHole::SetDirection(E_MOUSEHOLE_DIR dir)
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
