#pragma once
#include "../UIElement.h"
#include "../../GameObject/GameObject.h"
#include "../../GameObject/Tube.h"
struct GridItemInfo
{
	int m_x{ -1 };
	int m_y{ -1 };
	E_OBJTYPE obj_type = E_OBJTYPE::E_NULL;
	E_TUBE_TYPE tube_type = E_TUBE_TYPE::CROSS;
	int quantities = -1;
};

//TODO: should define new grid item inherit from griditem, griditem should be a interface
class GridItem
{
private:
	static int grid_id;
	int m_id = 0;

	Play::Point2D m_lefttop_pos;
	Play::Point2D m_rightbottom_pos;
	Play::Point2D m_pos;
	//Grid UI Info
	UIElement* m_element = nullptr;

public:
	GridItemInfo m_info;
	int m_height;
	int m_width;
public:

	GridItem();

	GridItem(Play::Point2D pos, int height, int width, int x, int y);

	void SetGridItem(UIElement* element);

	void SetItemInfo(UIElement* element);

	void DrawGrid(Play::Colour color = Play::cRed);

	void SetGridSize(int height, int width);

	void Clear();

	int GetID();

	bool OnHover();

	UIElement* GetGridUIElement();

	Play::Point2D GetPos();

	~GridItem();
};