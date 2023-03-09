#pragma once
#include <vector>
//Steps for new GameObject
// 1.Add enum type
// 2.Create Class inherit from GameObject class
// 3.Add new GameObject from ResourceMgr or Level
// 4.Update from GameObjectMgr
enum class E_OBJTYPE
{
	E_NULL = -1,
	E_MOUSE,
	E_TILE,
	E_BOUNDARY,
	E_MOUSETRAP,
	E_CHEESE,
	E_MOUSEHOLE,
	E_TUBE,
	E_STICKYSPILL,
	E_COFFEESPILL,
	E_CAT,
	E_HAMSTERBALL,
	E_MOTORSPRING,
	E_BELT,
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

	//control logic
	virtual void Update() = 0;
	//control how to render
	virtual void Render();

	virtual ~GameObject();

	int GetID();

	virtual void SetPosition(Play::Point2D pos);

	virtual void SetPosition(float x,float y);

	virtual void Rotate(float rot);

	virtual void SetScale(float scale);

	virtual void SetRotation(float rot);

	Play::Point2D& GetPosition();

	const char* GetSpriteName();

	void SetSpriteName(const char* name);

	//Draw ID Currnetly
	void DrawDebugInfo(Play::Colour color = Play::cRed);

};