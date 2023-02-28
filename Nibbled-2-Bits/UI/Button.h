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

	Button(float x, float y,  short height, short width, const char* spriteName = "", FunctionType OnClickHandler = [] {}, const char* btnName = "");

	Button(Play::Point2f pos, short height, short width,  const char* spriteName = "", FunctionType OnClickHandler = [] {}, const char* btnName = "");

	void SetSpriteName(const char* name);

	void Render() override;

	bool OnDrag();

	bool OnHover() override;

	bool OnClick() override;

	void AddOnClickHandler(FunctionType fun);
};



