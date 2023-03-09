#pragma once
#include "UIElement.h"
class TextField :public UIElement
{
private:
	std::string m_text{ "" };
public:
	TextField();
	TextField(Play::Point2f pos, short height, short width, std::string text = "", const char* spriteName = "");

	void Render() override;

	void SetText(std::string str);
};
