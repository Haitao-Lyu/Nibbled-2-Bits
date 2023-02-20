#include "pch.h"
#include "Button.h"
#include "../GameTool/DebugTool.h"
#include "UIManager.h"

Button::Button() :UIElement(Play::Point2D(0, 0), 0, 0)
{
	
}

Button::Button(float x, float y, const char* spriteName, short sprite_height, short sprite_width, FunctionType OnClickHandler, const char* btnName):UIElement(Play::Point2D(x, y), sprite_height, sprite_width)
{
	m_spriteName = spriteName;
	m_btnText = btnName;
	m_OnClickHandler = OnClickHandler;
}

Button::Button(Play::Point2f pos, const char* spriteName, short sprite_height, short sprite_width, FunctionType OnClickHandler, const char* btnName):UIElement(pos.x,pos.y, sprite_height, sprite_width)
{
	m_spriteName = spriteName;
	m_btnText = btnName;
	m_OnClickHandler = OnClickHandler;
}

void Button::SetSpriteName(const char* name)
{
	m_spriteName = name;
}

void Button::DrawSprite(float scale)
{
	Play::DrawSpriteRotated(m_spriteName, m_pos, 0, 0, scale, 1);
	Play::DrawDebugText(m_pos, m_btnText, Play::cRed, true);
}

bool Button::OnDrag()
{
	return UIElement::OnDrag();
}

bool Button::OnHover()
{
	return UIElement::OnHover();
}
bool Button::OnClick()
{
	if (UIElement::OnClick())
	{
		m_OnClickHandler();
		return true;
	}
	return false;
}


