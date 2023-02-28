#include "pch.h"
#include "UIElement.h"
#include "../GameTool/Math2D.h"
#include "../GameTool/DebugTool.h"

int UIElement::id = 0;


UIElement::UIElement(Play::Point2D _pos,short height, short width)
{
	m_id = id++;
	m_pos = _pos;
	m_height = height;
	m_width = width;
	SetCollisionBoundary();
}

UIElement::UIElement(float x, float y, short height, short width )
{
	m_id = id++;
	Play::Point2D _pos{ x,y };
	m_pos = _pos;
	m_height = height;
	m_width = width;
	SetCollisionBoundary();
}

void UIElement::Update()
{
	Render();
}

void UIElement::Render()
{
	if(std::strcmp(m_spriteName,"") != 0)
	Play::DrawSpriteRotated(m_spriteName, m_pos, 0, 0, m_scale, 1);
}

bool UIElement::OnClick()
{
	if (OnHover())
	{
		if (Play::KeyPressed(VK_LBUTTON))
		{
			DebugText("clicking");
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
		if (Play::GetMouseButton(Play::Align::LEFT))
		{

			DebugText("Dragging");
			return true;
		}
	}
	else
		return false;
}

bool UIElement::OnHolding()
{
	if (isHolding)
	{
		if (Play::KeyDown(VK_LBUTTON))
		{
			return true;
		}
		else
		{
			isHolding = false;
			return false;
		}
	}
	if (OnHover())
	{
		if (Play::KeyDown(VK_LBUTTON))
		{
			isHolding = true;
		}
	}
}

int UIElement::GetID()
{
	return m_id;
}

void UIElement::SetPosition(Play::Point2D pos)
{
	m_pos = pos;
	SetCollisionBoundary();
}

void UIElement::SetSpriteName(const char* name)
{
	m_spriteName = name;
}

void UIElement::SetCollisionBoundary()
{
	m_lefttop_pos = m_pos - Play::Point2D(m_width / 2, m_height / 2);
	m_rightbottom_pos = m_pos + Play::Point2D(m_width / 2, m_height / 2);
}

void UIElement::DrawBoundingBox(Play::Colour color)
{
	Play::DrawRect(m_lefttop_pos, m_rightbottom_pos, color);
	Play::DrawDebugText(m_pos, std::to_string(m_id).c_str(), color, true);
}

UIElement::~UIElement()
{

}