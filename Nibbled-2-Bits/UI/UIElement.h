#pragma once
#include "../pch.h"

class UIElement
{
protected:

public:
	static int id;
	int m_id;//when it's const the "=" operator is deleted ? ? 
	Play::Point2D m_pos{ 0.0f,0.0f };
	short m_height = 0;
	short m_width = 0;
	const char* m_spriteName = "";
	float m_scale = 1.0f;
	Play::Point2D m_lefttop_pos{ 0.0f,0.0f }, m_rightbottom_pos{ 0.0f,0.0f };

	UIElement() {}

	UIElement(Play::Point2D pos, short height = 100, short width = 50);

	UIElement(float x, float y, short height = 100, short width = 50);

	virtual void Render(float scale = 1.0f);

	virtual bool OnClick();

	virtual bool OnHover();

	virtual bool OnDrag();

	int GetID();

	virtual void SetPosition(Play::Point2D pos);

	void SetSpriteName(const char* name);

	void SetCollisionBoundary();

	void DrawBoundingBox(Play::Colour color = Play::cCyan);

	virtual ~UIElement();

};

