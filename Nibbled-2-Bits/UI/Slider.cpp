#include "pch.h"
#include "Slider.h"
#include "../GameTool/DebugTool.h"

Slider::Slider(Play::Point2D pos, const char* b_spriteName, short b_sprite_height, short b_sprite_width, const char* r_spriteName, short r_sprite_height, short r_sprite_width, const char* btn_text):
	UIElement(pos, b_sprite_height, r_sprite_width + b_sprite_width + 100)
{
	m_pos = pos;
	//btn init move slightly left
	btn = Button( {pos.x - b_sprite_width / 2,pos.y}, b_sprite_height, b_sprite_width);
	rect = RectFill{ pos,r_spriteName,r_sprite_height,r_sprite_width };
	SetText(btn_text);
	m_originX = btn.m_pos.x;
	m_length = r_sprite_width;
}

void Slider::ClampValue()
{
	if (btn.m_pos.x <= m_originX)
	{
		btn.m_pos.x = m_originX ;
	}
	if (btn.m_pos.x > m_originX + m_length)
	{
		btn.m_pos.x = m_originX + m_length;
	}
}

void Slider::SetText(const char* text)
{
	btn.m_btnText = text;
}

bool Slider::OnDrag()
{
	if (btn.OnDrag())
	{
		Play::Point2f clickPos = Play::GetMousePos();
		if (clickPos.x > m_lefttop_pos.x && clickPos.x < m_rightbottom_pos.x)
		{
			if (clickPos.y > m_lefttop_pos.y && clickPos.y < m_rightbottom_pos.y)
			{
				btn.m_pos.x = clickPos.x;
				ClampValue();
				btn.SetCollisionBoundary();
				m_value = static_cast<float>(btn.m_pos.x - m_originX) / static_cast<float>(m_length);
				DebugValue(m_value);
				return true;
			}
		}
	}
	return false;
}

bool Slider::OnHover()
{
	Play::Point2f clickPos = Play::GetMousePos();
	if (clickPos.x > m_lefttop_pos.x && clickPos.x < m_rightbottom_pos.x)
	{
		if (clickPos.y > m_lefttop_pos.y && clickPos.y < m_rightbottom_pos.y)
		{
			return true;
		}
	}
	return false;
}

float Slider::GetValue()
{
	return m_value;
}


void Slider::Render(float scale)
{
	rect.Render(scale);
	btn.Render(scale);
}
