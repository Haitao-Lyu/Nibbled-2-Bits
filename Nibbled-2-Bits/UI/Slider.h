#pragma once
#include "Button.h"
#include "RectFill.h"


class Slider :public UIElement
{
private:
	Button btn;
	RectFill rect;
	float m_value = 0;
	short m_length = 100;
	float m_originX = 0;

	void ClampValue();

public:
	Slider(Play::Point2D pos, const char* b_spriteName, short b_sprite_height, short b_sprite_width, const char* r_spriteName, short r_sprite_height, short r_sprite_width, const char* btn_text = "");

	float GetValue();

	void SetText(const char* text);

	bool OnDrag() override;

	bool OnHover() override;

	void DrawSprite(float scale = 1.0f) override;
};

