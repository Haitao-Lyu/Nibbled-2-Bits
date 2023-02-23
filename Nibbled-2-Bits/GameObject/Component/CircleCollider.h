#pragma once
#include "Collider.h"
class CircleCollider : public Collider
{

private:
	Play::Point2D m_pos{0.0f,0.0f};
	float m_radius{0.0f};
public:
	CircleCollider();

	CircleCollider(float radius, Play::Point2D pos);

	bool collidesWith(Collider& other)  override;

	void DrawBoundingBox(Play::Colour color = Play::cRed) override;

	void Init(Play::Point2D pos ,float radius) ;

	float GetRadius();

};

