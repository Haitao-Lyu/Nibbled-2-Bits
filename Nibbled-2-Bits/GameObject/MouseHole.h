#pragma once
#include "Boundary.h"
#include "Mouse.h"
#include "Boundary.h"

enum class E_MOUSEHOLE_DIR
{
	TOP,
	LEFT,
	BOTTOM,
	RIGHT
};
enum class E_MOUSEHOLE_TYPE
{
	ENTRY,
	EXIT,
};
class MouseHole:public Obstacle
{
private:
	int MouseToExit{ 0 };
	E_MOUSEHOLE_TYPE m_type = E_MOUSEHOLE_TYPE::ENTRY;
	E_BOUNDARY_COLOR m_color_type = E_BOUNDARY_COLOR::WHITE;
public:
	MouseHole(Play::Point2D pos, E_MOUSEHOLE_DIR dir = E_MOUSEHOLE_DIR::TOP);
	~MouseHole();

	void SetDirection(E_MOUSEHOLE_DIR dir);

	void OnMouseIn(Mouse& mouse);

	void SetType(E_MOUSEHOLE_TYPE _type);
};

