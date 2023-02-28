#pragma once
#include "../UIElement.h"

class GridItem
{
public:
	static int grid_id;
	int m_id = 0;
	short m_height;
	short m_width;

	Play::Point2D m_lefttop_pos;
	Play::Point2D m_rightbottom_pos;
	Play::Point2D m_pos;
	UIElement* m_element = nullptr;

	GridItem();

	GridItem(Play::Point2D pos, short height, short width);

	void AddGridItem(UIElement* element);

	void DrawGrid(Play::Colour color = Play::cRed);

	void SetGridSize(short height, short width);
};

class GridComponent
{
public:
	std::vector<std::vector<GridItem>> gridList = {};
	Play::Point2D m_pos;
	Play::Point2D m_lefttop_pos;
	Play::Point2D m_rightbottom_pos;
	short grid_row_num{ 0 };
	short grid_col_num{ 0 };
	short m_height;
	short m_width;

	GridComponent();

	GridComponent(Play::Point2D pos, short height = 100, short width = 100,short row = 2,short col = 2);

	void SetGridNum(short row, short col);

	Play::Point2D GetGridPos(int i, int j);

	void InitGridInfo(short row, short col, short height = 100, short width = 100,Play::Point2D pos  = {0.0f, 0.0f},short gridheight  = 0, short gridWidth = 0);

	void Render();

	void AddToGrids(UIElement* element);
};

