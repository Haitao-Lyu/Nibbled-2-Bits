#include "pch.h"
#include "GameObject.h"
#include "../GameTool/DebugTool.h"
#include "../Manager/GameObjectMgr.h"
#include "../MainGame.h"
int GameObject::total_id = 0;

GameObject::GameObject(Play::Point2D pos, E_OBJTYPE type)
{
	m_pos = pos;
	m_type = type;
	m_id = total_id;
	total_id++;
	GameObjectMgr::AddNewGameObject(*this);
}

GameObject::GameObject(float x, float y, E_OBJTYPE type)
{
	m_pos.x = x;
	m_pos.y = y;
	m_type = type;
	m_id = total_id;
	total_id++;
	GameObjectMgr::AddNewGameObject(*this);
}

GameObject::~GameObject()
{
}


int GameObject::GetID()
{
	return m_id;
}

void GameObject::SetPosition(Play::Point2D pos)
{
	m_pos = pos;
}

void GameObject::SetPosition(float x, float y)
{
	m_pos = { x,y };
}

void GameObject::Rotate(float rot)
{
	m_rot += rot;
}

void GameObject::SetScale(float scale)
{
	m_scale = scale;
}

void GameObject::SetRotation(float rot)
{
	while (rot < 0)
	{
		rot >= 360;
	}
	while (rot > 360)
	{
		rot -= 360;
	}
	m_rot = rot;
}

Play::Point2D& GameObject::GetPosition()
{
	return m_pos;
}

const char* GameObject::GetSpriteName()
{
	return spriteName;
}

void GameObject::SetSpriteName(const char* name)
{
	spriteName = name;
}

void GameObject::DrawDebugInfo(Play::Colour color)
{
	Play::DrawDebugText(m_pos, std::to_string(m_id).c_str(), color, true);
}

void GameObject::Render()
{
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale ,0.0f,0.0f },
		{ 0.0f,m_scale ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);
}

