#pragma once
#include "../GameObject.h"
#include "functional"
//penguien is not nesaserry to be a bird
class Collider {
public:
    static int id;
    int m_id = 0;
	GameObject* m_holderInfo = nullptr;
	GameObject* m_opponentInfo = nullptr;
public:
    Collider();
    virtual ~Collider() {}

    virtual bool collidesWith( Collider& other) = 0;

    int Getid();

    bool operator==(Collider& colldier) const;
};

class BoxCollider : public Collider {

private:
	Play::Point2D m_pos{ 0,0 };
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

	void DrawBoundingBox();

	void OnCollision(std::function<void()> fun);

	float GetWidth();

	float GetHeight();
};


class CircleCollider : public Collider {

private:
    Play::Point2D m_pos;
	float m_radius;
public:
    CircleCollider(float radius, Play::Point2D pos);

    bool collidesWith( Collider& other)  override;

};


