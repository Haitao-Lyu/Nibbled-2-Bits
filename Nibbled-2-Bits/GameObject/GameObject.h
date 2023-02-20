#pragma once

enum class E_OBJTYPE
{
	E_NULL = -1,
	E_MOUSE,
	E_TILE,
};
//The real obj in the game scene, must have position, must drawable
class GameObject 
{
public:
	static int m_id;
	E_OBJTYPE m_type = E_OBJTYPE::E_NULL;
	const char* spriteName = "";
	Play::Point2D m_pos{0.0f,0.0f};
public:
	GameObject(Play::Point2D pos, E_OBJTYPE m_type);

	GameObject(float x, float y, E_OBJTYPE m_type);
	
	virtual void operator=(GameObject&);

	virtual void Update() = 0;

	virtual void Render();

	virtual void DrawBoundingBox();

	virtual ~GameObject();

	int GetID();

	void SetPosition(Play::Point2D pos);

	void SetPosition(float x,float y);

	Play::Point2D& GetPosition();

	const char* GetSpriteName();

	void SetSpriteName(const char* name);

};