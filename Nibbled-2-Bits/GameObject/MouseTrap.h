#pragma once
#include "ConsumableObj.h"

enum class E_TRAPCOLOR
{
	DARK_WOOD,
	LIGHT_WOOD
};

class MouseTrap:public ConsumableObj
{

private:
	E_TRAPCOLOR m_color { E_TRAPCOLOR::DARK_WOOD };
public:
	MouseTrap(Play::Point2D pos, E_TRAPCOLOR color = E_TRAPCOLOR::DARK_WOOD);
	~MouseTrap();

	
};

