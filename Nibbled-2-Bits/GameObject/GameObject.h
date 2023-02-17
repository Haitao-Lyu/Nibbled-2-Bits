#pragma once
#include "../PlayCustom.h"

class GameObject 
{
private:
	static int m_id;
	const char* spriteName = "";
	Play::Point2D m_pos{0.0f,0.0f};
public:
	GameObject();
	
	virtual void operator=(GameObject&);

	int GetID();

	virtual void render();
};