#pragma once
#include "Collider.h"
class BoxCollider : public Collider {

private:
	Play::Point2D lt{ 0,0 };
	Play::Point2D lb{ 0,0 };
	Play::Point2D rt{ 0,0 };
	Play::Point2D rb{ 0,0 };
	float m_width{ 0.0f }, m_height{ 0.0f };
public:
	BoxCollider();

	BoxCollider(float width, float height, Play::Point2D pos, GameObject* info);

	void Init(float width, float height, Play::Point2D pos, GameObject* info);

	void UpdateShape(float width, float height, Play::Point2D pos);

	bool collidesWith(Collider& other)  override;

	void DrawBoundingBox(Play::Colour color = Play::cBlue);

	void OnCollision(std::function<void()> fun);

	float GetWidth();

	float GetHeight();

	Play::Point2D GetPos();
};



