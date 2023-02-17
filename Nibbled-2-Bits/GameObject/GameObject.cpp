#include "GameObject.h"

int GameObject::m_id = 0;

int GameObject::GetID()
{
	return m_id;
}

GameObject::GameObject()
{
	m_id++;
}

void GameObject::operator=(GameObject&)
{
	
}

void GameObject::render()
{
	Play::DrawSprite(spriteName,m_pos,0);
}
