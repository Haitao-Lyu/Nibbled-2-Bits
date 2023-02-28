#include "pch.h"
#include "GridItem.h"
int GridItem::grid_id;

GridItem::GridItem()
{

}

GridItem::GridItem(Play::Point2D pos, short height, short width)
{
	grid_id++;
	m_id = grid_id;
	m_pos = pos;
	m_height = height;
	m_width = width;
	m_lefttop_pos = m_pos - Play::Point2D(width / 2, height / 2);
	m_rightbottom_pos = m_pos + Play::Point2D(width / 2, height / 2);
}

void GridItem::AddGridItem(UIElement* element)
{
	m_element = element;
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