#pragma once
#include "../PlayCustom.h"

class UIElement
{
protected:
	
public:
	Play::Point2D m_pos{ 0.0f,0.0f };
	short m_height = 0, m_witdth = 0;
	const char* m_spriteName = "";
	Play::Point2D m_lefttop_pos{ 0.0f,0.0f }, m_rightbottom_pos{0.0f,0.0f};

	UIElement(Play::Point2D pos, short height, short width);

	UIElement(float x, float y, short height, short width);

	virtual void DrawSprite(float scale = 1.0f);

	virtual bool OnClick();

	virtual bool OnHover();

	virtual bool OnDrag();

	virtual void SetPosition(Play::Point2D pos);

	void SetCollisionBoundary();

	virtual ~UIElement();

};

