#include "pch.h"
#include "GridItem.h"
#include "../../Manager/GameObjectMgr.h"
int GridItem::grid_id;

static const char* tube_cross_name = "iron_tube_cross";
static const char* tube_one_name = "iron_tube_one_way";
static const char* tube_three_name = "iron_tube_three_way";
static const char* tube_two_name = "iron_tube_two_way";

GridItem::GridItem()
{

}

GridItem::GridItem(Play::Point2D pos, short height, short width,short x,short y)
{
	grid_id++;
	m_id = grid_id;
	m_pos = pos;
	m_height = height;
	m_width = width;
	m_info.m_x = x;
	m_info.m_y = y;
	m_lefttop_pos = m_pos - Play::Point2D(width / 2, height / 2);
	m_rightbottom_pos = m_pos + Play::Point2D(width / 2, height / 2);
}

void GridItem::SetGridItem(UIElement* element)
{
	SetItemInfo(element);
	m_element = element;
}

//Set UI Item info base on name ? ? doesn't seem right
void GridItem::SetItemInfo(UIElement* element)
{
	if (std::strcmp(element->m_spriteName, tube_cross_name) == 0)
	{
		m_info.tube_type = E_TUBE_TYPE::CROSS;
		m_info.obj_type = E_OBJTYPE::E_TUBE;
	}
	if (std::strcmp(element->m_spriteName, tube_one_name) == 0)
	{
		m_info.tube_type = E_TUBE_TYPE::ONEWAY;
		m_info.obj_type = E_OBJTYPE::E_TUBE;
	}
	if (std::strcmp(element->m_spriteName, tube_two_name) == 0)
	{
		m_info.tube_type = E_TUBE_TYPE::TWOWAY;
		m_info.obj_type = E_OBJTYPE::E_TUBE;
	}
	if (std::strcmp(element->m_spriteName, tube_three_name) == 0)
	{
		m_info.tube_type = E_TUBE_TYPE::THREEWAY;
		m_info.obj_type = E_OBJTYPE::E_TUBE;
	}
}

void GridItem::DrawGrid(Play::Colour color /*= Play::cRed*/)
{
	Play::DrawRect(m_lefttop_pos, m_rightbottom_pos, color);
	Play::DrawDebugText(m_pos, std::to_string(m_id).c_str(), color, true);
}


void GridItem::SetGridSize(short height, short width)
{
	m_height = height;
	m_width = width;
}

void GridItem::Clear()
{
	m_element = nullptr;
}

int GridItem::GetID()
{
	return m_id;
}

bool GridItem::OnHover()
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

UIElement* GridItem::GetGridUIElement()
{
	return m_element;
}

Play::Point2D GridItem::GetPos()
{
	return m_pos;
}
