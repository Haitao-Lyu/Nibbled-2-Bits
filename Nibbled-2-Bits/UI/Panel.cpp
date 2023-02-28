#include "pch.h"
#include "Panel.h"
#include "../GameTool/DebugTool.h"
#include "../MainGame.h"
#include "EventCenter.h"
Panel::Panel(Play::Point2D pos, short height, short width, const char* spriteName) : UIElement(pos, height, width)
{
	m_lt_pos = { m_pos.x - width / 2, m_pos.y - height / 2 };
	m_lb_pos = { m_pos.x - width / 2, m_pos.y + height / 2 };
	m_rt_pos = { m_pos.x + width / 2, m_pos.y - height / 2 };
	m_rb_pos = { m_pos.x + width / 2, m_pos.y + height / 2 };
	m_spriteName = spriteName;
	gridComponent.InitGridInfo(3,3, height, width, pos);
}

Panel::~Panel()
{
}

void Panel::Update()
{

	Render();
}

void Panel::Render()
{
	if (std::strcmp(m_spriteName, "") != 0)
	{
		y_scale = static_cast<float>(m_height) / Play::GetSpriteHeight(m_spriteName);
		x_scale = static_cast<float>(m_width) / Play::GetSpriteWidth(m_spriteName);
		const Play::Matrix2D scaleMt = Play::Matrix2D(
			{ x_scale,0.0f,0.0f },
			{ 0.0f,y_scale,0.0f },
			{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
		Play::DrawSpriteTransformed(Play::GetSpriteId(m_spriteName), scaleMt, 0);
	}
	//debug grid
	gridComponent.Render();
}
