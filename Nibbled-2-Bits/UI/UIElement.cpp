#include "pch.h"
#include "UIElement.h"
#include "../GameTool/Math2D.h"
#include "../GameTool/DebugTool.h"

UIElement::UIElement(Play::Point2D _pos, short height, short width)
{
	m_pos = _pos;
	m_height = height;
	m_witdth = width;
	SetCollisionBoundary();
}

UIElement::UIElement(float x, float y, short height, short width)
{
	Play::Point2D _pos{ x,y };
	m_pos = _pos;
	m_height = height;
	m_witdth = width;
	SetCollisionBoundary();
}

void UIElement::DrawSprite(float scale)
{
	Play::DrawSpriteRotated(m_spriteName, m_pos, 0, 0, scale, 1);
}

bool UIElement::OnClick()
{
	if (OnHover())
	{
		if (Play::KeyPressed(VK_LBUTTON))
		{
			//DebugText("clicking");
			return true;
		}
	}
	return false;
}

bool UIElement::OnHover()
{
	Play::Point2f clickPos = Play::GetMousePos();
	if (clickPos.x > m_lefttop_pos.x && clickPos.x < m_rightbottom_pos.x)
	{
		if (clickPos.y > m_lefttop_pos.y && clickPos.y < m_rightbottom_pos.y)
		{
			//DebugText("Hovering");
			return true;
		}
	}
	return false;
}

bool UIElement::OnDrag()
{
	if (OnHover())
	{
		if (Play::KeyDown(VK_LBUTTON))
		{
			//DebugText("Dragging");
			return true;
		}
	}
	return false;
}

void UIElement::SetPosition(Play::Point2D pos)
{
	m_pos = pos;
}

void UIElement::SetCollisionBoundary()
{
	m_lefttop_pos = m_pos - Play::Point2D(m_witdth / 2, m_height / 2);
	m_rightbottom_pos = m_pos + Play::Point2D(m_witdth / 2, m_height / 2);
}

UIElement::~UIElement()
{

}