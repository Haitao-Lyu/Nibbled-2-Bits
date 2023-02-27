#include "pch.h"
#include "GridComponent.h"
#include "../../GameTool/DebugTool.h"
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


GridComponent::GridComponent()
{
	m_pos = { 0.0f,0.0f };
	m_height = 100;
	m_width = 100;
	SetGridNum(2,2);
}

GridComponent::GridComponent(Play::Point2D pos, short height, short width, short row , short col )
{
	m_pos = pos;
	m_height = height;
	m_width = width;
	SetGridNum(row, col);
}

void GridComponent::SetGridNum(short row, short col)
{
	grid_col_num = col;
	grid_row_num = row;
}

void GridItem::SetGridSize(short height, short width)
{
	m_height = height;
	m_width = width;
}

void GridComponent::InitGridInfo(short row, short col, short height, short width, Play::Point2D pos, short gridheight , short gridWidth)
{
	m_pos = pos;
	m_lefttop_pos = m_pos - Play::Point2D(width / 2, height / 2);
	m_rightbottom_pos = m_pos + Play::Point2D(width / 2, height / 2);

	SetGridNum(row, col);
	m_height = height;
	m_width = width;
	m_childlist.resize(grid_col_num * grid_row_num);
	short grid_width;
	short grid_height;
	if (gridheight == 0 || gridWidth == 0)
	{
		grid_width = m_width / grid_col_num;
		grid_height = m_height / grid_row_num;
	}
	else
	{
		grid_width = gridWidth;
		grid_height = gridheight;
	}
	int index = 0;
	for (int j = 0; j < grid_row_num; j++)
	{
		for (int i = 0; i < grid_col_num; i++)
		{
			Play::Point2D pos = { m_lefttop_pos.x + i * grid_width + grid_width / 2, m_lefttop_pos.y + j * grid_height + grid_height / 2 };
			GridItem grid(pos, grid_height, grid_width);
			m_childlist[index++] = grid;
		}
	}

}

void GridComponent::Render()
{
	DebugValue((int)m_childlist.size());
	for (GridItem& grid : m_childlist)
	{
		//debug grids
		grid.DrawGrid();
		//if has uielement
		if (grid.m_element)
		{
			grid.m_element->Render(1.0f);
			if (grid.m_element->OnDrag())
			{
				UIElement btn;
				btn.SetSpriteName(grid.m_element->m_spriteName);
				btn.SetPosition(Play::GetMousePos());
				btn.Render(0.5);
			}
			else
			{
				//release mouse button
			}
		}
	}
}

void GridComponent::AddToGrids(UIElement* element)
{
	for (GridItem& grid : m_childlist)
	{
		if (grid.m_element)
			continue;
		else
		{
			element->SetPosition(grid.m_pos);
			grid.m_element = element;
			break;
		}
	}
}
