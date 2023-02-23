#pragma once
#include <vector>
enum class E_OBJTYPE
{
	E_NULL = -1,
	E_MOUSE,
	E_TILE,
	E_BOUNDARY,
	E_MOUSETRAP,
	E_CHEESE,
	E_MOUSEHOLE,
};
//The real obj in the game scene, must have position, must drawable
class GameObject 
{
public:
	static int total_id;
	int m_id = 0;
	E_OBJTYPE m_type = E_OBJTYPE::E_NULL;
	const char* spriteName = "";
	Play::Point2D m_pos{0.0f,0.0f};
	float m_rot = 0;
	float m_scale{ 1.0f };
	float m_spriteHeight = 0;
	float m_spriteWidth = 0;
public:
	GameObject(Play::Point2D pos, E_OBJTYPE m_type);

	GameObject(float x, float y, E_OBJTYPE m_type);
	
	virtual void operator=(GameObject&);
	//control logic
	virtual void Update() = 0;
	//control how to render
	virtual void Render();

	virtual ~GameObject();

	int GetID();

	void SetPosition(Play::Point2D pos);

	void SetPosition(float x,float y);

	Play::Point2D& GetPosition();

	const char* GetSpriteName();

	void SetSpriteName(const char* name);

};