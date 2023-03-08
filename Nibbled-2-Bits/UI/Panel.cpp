#include "pch.h"
#include "Panel.h"
#include "../GameTool/DebugTool.h"
#include "../MainGame.h"
#include "EventCenter.h"
Panel::Panel(Play::Point2D pos, float height, float width, const char* spriteName) : UIElement(pos, height, width)
{
	m_lt_pos = { m_pos.x - width / 2, m_pos.y - height / 2 };
	m_lb_pos = { m_pos.x - width / 2, m_pos.y + height / 2 };
	m_rt_pos = { m_pos.x + width / 2, m_pos.y - height / 2 };
	m_rb_pos = { m_pos.x + width / 2, m_pos.y + height / 2 };
	m_spriteName = spriteName;
	gridComponent.InitGridInfo(2, 3, m_height, m_width, { m_pos.x, m_pos.y });
}
 
Panel::~Panel()
{
	
}

void Panel::SetScale(float x, float y)
{
	x_scale = x;
	y_scale = y;
	m_height *= y_scale;
	m_width *= x_scale;
	gridComponent.InitGridInfo(2, 3, m_height, m_width , { m_pos.x, m_pos.y });
	m_lt_pos = { m_pos.x - m_width / 2, m_pos.y - m_height / 2 };
	m_lb_pos = { m_pos.x - m_width / 2, m_pos.y + m_height / 2 };
	m_rt_pos = { m_pos.x + m_width / 2, m_pos.y - m_height / 2 };
	m_rb_pos = { m_pos.x + m_width / 2, m_pos.y + m_height / 2 };
	m_lefttop_pos = m_lt_pos;
	m_rightbottom_pos = m_rb_pos;
}

void Panel::SetSpriteScale(float x, float y)
{
	x_scale = x;
	y_scale = y;
}

void Panel::Update()
{
	if (isVisable)
	{
		Render();
		for (UIElement* ui : childList)
		{
			ui->Update();
		}
	}
}

void Panel::Render()
{
	if (std::strcmp(m_spriteName, "") != 0)
	{
		const Play::Matrix2D scaleMt = Play::Matrix2D(
			{ x_scale,0.0f,0.0f },
			{ 0.0f,y_scale,0.0f },
			{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
		Play::DrawSpriteTransformed(Play::GetSpriteId(m_spriteName), scaleMt, 0);
	}
	//debug grid
	gridComponent.Render();
	DrawBoundingBox();
}

void Panel::AddToPanel(UIElement* UIelement)
{
	childList.push_back(UIelement);
}

void Panel::SetVisibility(bool value)
{
	for (UIElement* ui : childList)
	{
		ui->isVisable = value;
	}
	for (std::vector<GridItem>& itemlist : gridComponent.gridList)
	{
		for (GridItem& obj : itemlist)
		{
			UIElement* ptr = obj.GetGridUIElement();
			if(ptr)
				ptr->isVisable = value;
		}
	}
	this->isVisable = value;
}

void Panel::Clear()
{
	for (UIElement* ui : childList)
	{
		delete ui;
	}
	childList.clear();
	gridComponent.Clear();
}

void Panel::SetActive(bool value)
{
	for (UIElement* ui : childList)
	{
		ui->isActive = value;
	}
	for (std::vector<GridItem> &itemlist: gridComponent.gridList)
	{
		for (GridItem &obj : itemlist)
		{
			UIElement* ptr = obj.GetGridUIElement();
			if (ptr)
				ptr->isActive = value;
		}
	}
	this->isVisable = value;
}