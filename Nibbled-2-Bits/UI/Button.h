#pragma once

#include "../GameTool/Math2D.h"
#include "UIElement.h"
#include <vector>
#include <functional>

class Button : public UIElement
{
	typedef std::function<void()> FunctionType;
private:
	FunctionType m_OnClickHandler;
public:
	const char* m_btnText{ "BUTTON" };

	Button();

	Button(float x, float y,  short sprite_height, short sprite_width, FunctionType OnClickHandler = [] {}, const char* spriteName = "", const char* btnName = "BUTTON");

	Button(Play::Point2f pos, short sprite_height, short sprite_width, FunctionType OnClickHandler = [] {}, const char* spriteName = "", const char* btnName = "BUTTON");

	void SetSpriteName(const char* name);

	void Render(float scale = 1.0f) override;

	bool OnDrag();

	bool OnHover() override;

	bool OnClick() override;
};



