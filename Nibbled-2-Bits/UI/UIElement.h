#pragma once
#include "../pch.h"

class UIElement
{
protected:
	float m_scale = 1.0f;

public:
	Play::Point2D m_pos{ 0.0f,0.0f };
	Play::Point2D m_lefttop_pos{ 0.0f,0.0f };
	Play::Point2D m_rightbottom_pos{ 0.0f,0.0f };
	float m_rot = 0.0f;
	const char* m_spriteName = "";
	static int id;
	int m_id;//when it's const the "=" operator is deleted ? ? 
	short m_height = 0;
	short m_width = 0;
	bool isHolding = false;
	bool isActive = true;
	bool isVisable = true;
	//TODO : Copy consturctor and  = overload
	UIElement() {}

	UIElement(Play::Point2D pos, short height = 100, short width = 50);

	UIElement(float x, float y, short height = 100, short width = 50);

	virtual void Update();

	virtual void Render();

	virtual bool OnClick();

	virtual bool OnClickRight();

	virtual bool OnHover();

	virtual bool OnDrag();

	virtual bool OnHolding();

	int GetID();

	virtual void SetPosition(Play::Point2D pos);

	void SetRotation(float rot);

	void SetSpriteName(const char* name);

	void SetCollisionBoundary();

	void DrawBoundingBox(Play::Colour color = Play::cCyan);

	virtual ~UIElement();

};

