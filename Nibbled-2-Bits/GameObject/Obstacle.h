#pragma once
#include "GameObject.h"
#include "Component/BoxCollider.h"
#include "Component/CircleCollider.h"
//not all penguien need to be a bird
//which way is better perpare base class ahead or create it when shared feature show up
class Obstacle:public GameObject
{
protected:
	BoxCollider m_boxCollider;
	CircleCollider m_circleCollider;
public:
	Obstacle(Play::Point2D pos,E_OBJTYPE type);
	virtual ~Obstacle();

	virtual void Update() override;
	virtual void Render() override;


	BoxCollider& GetBoxCollider();
	CircleCollider& GetCollider();

	void SetPosition(Play::Point2D pos) override;

	void SetPosition(float x, float y) override;

};

