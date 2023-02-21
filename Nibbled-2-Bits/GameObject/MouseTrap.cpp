#include "pch.h"
#include "MouseTrap.h"

static const char* trap_dark_wood = "Trap_dark_wood";
static const char* trap_dark_wood_not = "Trap_dark_wood_not";
static const char* trap_light_wood =	"Trap_light_wood";
static const char* trap_light_wood_not = "Trap_light_wood_not";

MouseTrap::MouseTrap(Play::Point2D pos, E_TRAPCOLOR color):ConsumableObj(pos,E_OBJTYPE::E_MOUSETRAP),m_color(color)
{
	switch (m_color)
	{
	case E_TRAPCOLOR::DARK_WOOD:
		spriteName = trap_dark_wood;
		break;
	case E_TRAPCOLOR::LIGHT_WOOD:
		spriteName = trap_light_wood;
		break;
	default:
		break;
	}
}

MouseTrap::~MouseTrap()
{
}