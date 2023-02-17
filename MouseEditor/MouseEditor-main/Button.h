#pragma once
#include "Play.h"

class Button
{
public:
	Button();
	Button(int, Play::Point2D, Play::Vector2D);

	virtual void Update();
	virtual void Draw();

	virtual bool Pressed();
	virtual bool Held();
	virtual bool Hovering();

	virtual void DrawSprite(Play::Point2D position);

	virtual void SetPos(Play::Point2D pos);

	Play::Vector2D GetSize();

protected:
	Play::Point2D m_pos;
	int m_sprite;
	Play::Vector2D m_size;

private:

};