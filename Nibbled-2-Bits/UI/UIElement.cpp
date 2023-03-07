#include "pch.h"
#include "UIElement.h"
#include "../GameTool/Math2D.h"
#include "../GameTool/DebugTool.h"
#include "../MainGame.h"
int UIElement::id = 0;


UIElement::UIElement()
{
}

UIElement::UIElement(Play::Point2D _pos, float height, float width)
{
	m_id = id++;
	m_pos = _pos;
	m_height = height;
	m_width = width;
	SetCollisionBoundary();
}

UIElement::UIElement(float x, float y, float height, float width )
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
	if(isVisable)
	Render();
}

void UIElement::Render()
{
	if (std::strcmp(m_spriteName, "") != 0)
	{
		Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));

		const Play::Matrix2D scaleMt = Play::Matrix2D(
			{ m_scale,0.0f,0.0f },
			{ 0.0f,m_scale,0.0f },
			{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
		Play::DrawSpriteTransformed(Play::GetSpriteId(m_spriteName), scaleMt * rotMt, 0);
	}
}

bool UIElement::OnClick()
{
	if (!isActive)
		return false;
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

bool UIElement::OnClickRight()
{
	if (!isActive)
		return false;
	if (OnHover())
	{
		if (Play::KeyPressed(VK_RBUTTON))
		{
			DebugText("clicking");
			return true;
		}
	}
	return false;
}

bool UIElement::OnHover()
{
	if (!isActive)
		return false;
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
	if (!isActive)
		return false;
	if (!isDragable)
		return false;
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
	if (!isActive)
		return false;
	if (!isDragable)
		return false;
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

	if(OnClick())
	{
		isHolding = true;	
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

void UIElement::SetRotation(float rot)
{
	m_rot = rot;
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