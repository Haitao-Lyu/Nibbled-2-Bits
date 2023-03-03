#include "pch.h"
#include "GridComponent.h"
#include "../../GameTool/DebugTool.h"

GridComponent::GridComponent()
{
	m_pos = { 0.0f,0.0f };
	m_height = 100;
	m_width = 100;
	SetGridNum(2, 2);
}

GridComponent::GridComponent(Play::Point2D pos, short height, short width, short row, short col)
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

Play::Point2D GridComponent::GetGridPos(int i, int j)
{
	if (i < gridList.size() && i >= 0)
		if (j < gridList[0].size() && j >= 0)
			return gridList[i][j].GetPos();
	
	return Play::Point2D{ 0,0 };
}


void GridComponent::InitGridInfo(short row, short col, short height, short width, Play::Point2D pos, short gridheight , short gridWidth)
{
	m_pos = pos;
	m_lefttop_pos = m_pos - Play::Point2D(width / 2, height / 2);
	m_rightbottom_pos = m_pos + Play::Point2D(width / 2, height / 2);

	SetGridNum(row, col);
	m_height = height;
	m_width = width;

	gridList.resize(grid_col_num);
	for (std::vector<GridItem>& grids : gridList)
		grids.resize(grid_row_num);

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
			GridItem grid(pos, grid_height, grid_width,i,j);
			gridList[i][j] = grid;
		}
	}

}

void GridComponent::Render()
{
	DebugValue((int)gridList.size());
	for (std::vector<GridItem>& grids : gridList)
	for (GridItem& grid : grids)
	{
		//debug grids
		grid.DrawGrid();
		//if has ui element
		if (grid.GetGridUIElement())
		{
			grid.GetGridUIElement()->Render();
		}
	}
}

void GridComponent::RemoveGridItemByID(int id)
{
	for (std::vector<GridItem>& grids : gridList)
		for (GridItem& grid : grids)
		{
			if (grid.GetID() == id)
			{
				grid.Clear();
			}
		}
}

void GridComponent::Push_back_Grids(UIElement* element)
{
	bool isAdded = false;
	for (int j = 0; j < gridList[0].size(); j++)
	{
		if (isAdded)
			break;
		for (int i = 0; i < gridList.size(); i++)
		{
			if (isAdded)
				break;
			if (gridList[i][j].GetGridUIElement())
				continue;
			else
			{
				element->SetPosition(gridList[i][j].GetPos());
				gridList[i][j].SetGridItem(element);
				isAdded = true;
				break;
			}
		}
	}

}

void GridComponent::AddToGrids(UIElement* element, short x, short y)
{
	element->SetPosition(gridList[x][y].GetPos());
	gridList[x][y].SetGridItem(element);
}

Play::Point2D GridComponent::GetPos()
{
	return m_pos;
}
