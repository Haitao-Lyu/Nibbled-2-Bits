#include "pch.h"
#include "ClickableObj.h"

ClickableObj::ClickableObj(Play::Point2D pos, E_OBJTYPE type):GameObject(pos,type)
{

}

ClickableObj::~ClickableObj()
{

}

void ClickableObj::Update()
{

}

void ClickableObj::Render()
{

}

bool ClickableObj::OnDrag()
{
	return false;
}

bool ClickableObj::OnHover()
{
	return false;
}

bool ClickableObj::OnClick()
{
	return false;
}

CircleCollider& ClickableObj::GetCollider()
{
	return m_circleCollider;
}

