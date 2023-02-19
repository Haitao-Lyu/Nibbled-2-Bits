#include "Panel.h"

Panel::Panel(Play::Point2D pos, short height, short width) : UIElement(pos, height, width)
{
}

Panel::~Panel()
{
}

void Panel::AddToPanel(UIElement& uielement)
{
	m_childlist.push_back(uielement);
}

void Panel::Render()
{
	for (UIElement& element: m_childlist)
	{
		element.DrawSprite(1.0f);
	}
}
