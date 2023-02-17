#pragma once
#include "UIElement.h"
class RectFill :public UIElement
{
private:

public:
	RectFill();
	RectFill(Play::Point2f pos, const char* spriteName, short sprite_height, short sprite_width);
};

