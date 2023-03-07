#pragma once
#include "UIElement.h"
class RectFill :public UIElement
{
private:

public:
	RectFill();
	RectFill(Play::Point2f pos, short height, short width, const char* spriteName = "");

	void Render() override;
};

