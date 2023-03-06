#include "pch.h"
#include "GridComponent.h"
#include "../../GameTool/DebugTool.h"
#include "../../Manager/ResourceMgr.h"
GridComponent::GridComponent()
{
	m_pos = { 0.0f,0.0f };
	m_height = 100;
	m_width = 100;
	SetGridNum(2, 2);
}

GridComponent::GridComponent(Play::Point2D pos, int height, int width, int row, int col)
{
	m_pos = pos;
	m_height = height;
	m_width = width;
	SetGridNum(row, col);
}

void GridComponent::SetGridNum(int row, int col)
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


void GridComponent::InitGridInfo(int row, int col, int height, int width, Play::Point2D pos, int gridheight , int gridWidth)
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

	int grid_width;
	int grid_height;
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
	for (int j = 0; j < grid_row_num; j++)
	{
		for (int i = 0; i < grid_col_num; i++)
		{
			Play::Point2D temppos = { m_lefttop_pos.x + i * grid_width + grid_width / 2, m_lefttop_pos.y + j * grid_height + grid_height / 2 };
			GridItem grid(temppos, grid_height, grid_width,i,j);
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
		//if has ui element, draw it
		if (grid.GetGridUIElement())
		{
			grid.GetGridUIElement()->Render();
			if (grid.m_info.quantities > -1)
			{
				//no need to be here
				Play::DrawFontText(ResoureMgr::GetFontName(E_FONTS::BOLD_64), ("x" + std::to_string(grid.m_info.quantities)).c_str(), {grid.GetPos().x + grid.m_width / 3, grid.GetPos().y}, Play::Align::CENTRE);
			}
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

GridItem* GridComponent::Push_back_Grids(UIElement* element)
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
				return &gridList[i][j];
			}
		}
	}
	return nullptr;
}

void GridComponent::AddToGrids(UIElement* element, int x, int y)
{
	element->SetPosition(gridList[x][y].GetPos());
	gridList[x][y].SetGridItem(element);
}

void GridComponent::AddItem(UIElement* element)
{
	int pass_id = Play::GetSpriteId(element->m_spriteName);
	for (std::vector<GridItem>& grids : gridList)
	{
		for (GridItem& grid : grids)
		{
			int grid_id = -1;
			if(grid.GetGridUIElement())
				grid_id = Play::GetSpriteId(grid.GetGridUIElement()->m_spriteName);
			if (pass_id == grid_id)
			{
				grid.m_info.quantities++;
				return;
			}
		}
	}
	Push_back_Grids(element);

}

Play::Point2D GridComponent::GetPos()
{
	return m_pos;
}

GridComponent::~GridComponent()
{
	gridList.clear();
	delete heldGridItem;
	heldGridItem = nullptr;
}
