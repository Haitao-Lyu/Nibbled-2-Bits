#include "GameObject.h"
#include "../GameTool/DebugTool.h"
#include "GameObjectMgr.h"
int GameObject::m_id = 0;


GameObject::GameObject(Play::Point2D pos, E_OBJTYPE type)
{
	m_pos = pos;
	m_type = type;
	m_id++;
	GameObjectMgr::AddNewGameObject(*this);
}

GameObject::GameObject(float x, float y, E_OBJTYPE type)
{
	m_pos.x = x;
	m_pos.y = y;
	m_type = type;
	m_id++;
	GameObjectMgr::AddNewGameObject(*this);
}

void GameObject::operator=(GameObject&)
{

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

void GameObject::DrawBoundingBox()
{
	Play::Point2D tl{ m_pos.x - Play::GetSpriteWidth(spriteName) / 2,m_pos.y - Play::GetSpriteHeight(spriteName) / 2 };
	Play::Point2D br{ m_pos.x + Play::GetSpriteWidth(spriteName) / 2,m_pos.y + Play::GetSpriteHeight(spriteName) / 2 };
	Play::DrawRect(tl, br, Play::cRed);
}

void GameObject::Render()
{
	if(std::strcmp(spriteName,"") == 1)//if has name
	Play::DrawSprite(spriteName,m_pos,0);
}

