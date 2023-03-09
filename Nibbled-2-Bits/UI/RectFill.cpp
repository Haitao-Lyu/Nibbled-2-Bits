#include "pch.h"
#include "RectFill.h"
RectFill::RectFill():UIElement({ 0,0 }, 0, 0)
{
	
}

RectFill::RectFill(Play::Point2f pos, short height, short width, const char* spriteName) : UIElement(pos, height, width)
{
	m_spriteName = spriteName;
}

void RectFill::Render()
{
	UIElement::Render();
	//DrawBoundingBox();
}
