#pragma once
#include "GameObject.h"
#include "Component/BoxCollider.h"
#include "Component/CircleCollider.h"
//not all penguien need to be a bird
//which way is better perpare base class ahead or create it when shared feature show up
class ClickableObj :public GameObject
{
protected:
	CircleCollider m_circleCollider;
	bool isHolding = false;
	Play::Point2D m_lefttop_pos{ 0.0f,0.0f };
	Play::Point2D m_rightbottom_pos{ 0.0f,0.0f };
public:

	ClickableObj(Play::Point2D pos, E_OBJTYPE type);

	~ClickableObj();

	virtual void Update() override;
	virtual void Render() override;

	virtual bool OnDrag();

	virtual bool OnHover();

	virtual bool OnClick();

	CircleCollider& GetCollider();
};
