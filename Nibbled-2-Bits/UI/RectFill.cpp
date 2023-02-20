#include "pch.h"
#include "RectFill.h"
RectFill::RectFill():UIElement({ 0,0 }, 0, 0)
{
	
}

RectFill::RectFill(Play::Point2f pos, const char* spriteName, short sprite_height, short sprite_width) : UIElement(pos, sprite_height, sprite_width)
{
	m_spriteName = spriteName;
}
