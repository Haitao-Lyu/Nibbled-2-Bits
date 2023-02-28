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
	//Grid UI Info
	UIElement* m_element = nullptr;

	GridItem();

	GridItem(Play::Point2D pos, short height, short width);

	void AddGridItem(UIElement* element);

	void DrawGrid(Play::Colour color = Play::cRed);

	void SetGridSize(short height, short width);

	bool OnHover();

};