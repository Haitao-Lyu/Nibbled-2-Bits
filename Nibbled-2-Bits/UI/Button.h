#pragma once

#include "../GameTool/Math2D.h"
#include "UIElement.h"
#include <vector>
#include <functional>

class Button : public UIElement
{
	typedef std::function<void()> FunctionType;
private:
	FunctionType m_OnClickHandler{ [](){} };
	FunctionType m_OnHoverHandler{ [](){} };
	float m_hoverScale{1.0f};

public:
	const char* m_btnText{ "BUTTON" };

	Button();

	Button(float x, float y,  short height, short width, const char* spriteName = "", FunctionType OnClickHandler = [] {}, const char* btnName = "");

	Button(Play::Point2f pos, short height, short width,  const char* spriteName = "", FunctionType OnClickHandler = [] {}, const char* btnName = "");

	void SetSpriteName(const char* name);

	void Render() override;

	bool OnDrag() override;

	bool OnHover() override;

	bool OnClick() override;

	void AddOnClickHandler(FunctionType fun);

	void AddOnHoverHandler(FunctionType fun);
};



