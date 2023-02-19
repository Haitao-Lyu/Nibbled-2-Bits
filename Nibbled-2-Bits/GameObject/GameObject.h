#pragma once
#include "../PlayCustom.h"

//The real obj in the game scene, must have position, must drawable
class GameObject 
{
protected:
	static int m_id;
	const char* spriteName = "";
	Play::Point2D m_pos{0.0f,0.0f};
public:
	GameObject(Play::Point2D pos);

	GameObject(float x, float y);
	
	virtual void operator=(GameObject&);

	virtual void Update() = 0;

	virtual void Render();

	virtual ~GameObject();

	int GetID();

	void SetPosition(Play::Point2D pos);

	void SetPosition(float x,float y);

	Play::Point2D& GetPosition();

	const char* GetSpriteName();

	void SetSpriteName(const char* name);

	virtual void DrawBoundingBox();
};