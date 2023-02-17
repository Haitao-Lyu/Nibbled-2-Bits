#pragma once
#include "../PlayCustom.h"
#include <vector>
#include "UIElement.h"
class Panel:public UIElement
{
private:
	std::vector<UIElement> m_childlist;
public:
	Panel(Play::Point2D pos, float height , float width);
	~Panel();

	void AddToPanel(UIElement& uielement);

	void Render();
};
