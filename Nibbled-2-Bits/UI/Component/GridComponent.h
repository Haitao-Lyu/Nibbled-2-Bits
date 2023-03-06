#pragma once
#include "GridItem.h"
class GridComponent
{
private:
	Play::Point2D m_pos;
	Play::Point2D m_lefttop_pos;
	Play::Point2D m_rightbottom_pos;

	int grid_row_num{ 0 };
	int grid_col_num{ 0 };
	int m_height;
	int m_width;
public:
	std::vector<std::vector<GridItem>> gridList = {};

	GridItem* heldGridItem = nullptr;

	GridComponent();

	GridComponent(Play::Point2D pos, int height = 100, int width = 100,int row = 2,int col = 2);

	void SetGridNum(int row, int col);

	Play::Point2D GetGridPos(int i, int j);

	void InitGridInfo(int row, int col, int height = 100, int width = 100,Play::Point2D pos  = {0.0f, 0.0f},int gridheight  = 0, int gridWidth = 0);

	void Render();

	void RemoveGridItemByID(int id);

	GridItem* Push_back_Grids(UIElement* element);

	void AddToGrids(UIElement* element,int x,int y);

	void AddItem(UIElement* element);

	Play::Point2D GetPos();

	~GridComponent();
};

