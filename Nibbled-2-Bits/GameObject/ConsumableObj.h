#pragma once

#include "GameObject.h"
#include "Component/BoxCollider.h"
#include "Component/CircleCollider.h"
//Calculate Collision but won't block
class ConsumableObj:public GameObject
{

protected:
	BoxCollider m_boxCollider;
	CircleCollider m_circleCollider;
	float m_scale = 1.0f;
	float m_spriteHeight{ 0.0f };
	float m_spriteWidth{ 0.0f };
	bool isConsumed = false;
	ConsumableObj() = delete;
public:
	ConsumableObj(Play::Point2D pos, E_OBJTYPE type);
	~ConsumableObj();

	virtual void Update() override;
	virtual void Render() override;

	void SetIsConsumed(bool value);

	BoxCollider& GetBoxCollider();

	CircleCollider& GetCollider();
};

