#pragma once
#include "UIElement.h"
class TextField :public UIElement
{
private:
	const char* m_text = "";
public:
	TextField();
	TextField(Play::Point2f pos, short height, short width, const char* text = "", const char* spriteName = "");

	void Render() override;

	void SetText(const char* text);
};
