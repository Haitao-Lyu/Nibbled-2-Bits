#include "pch.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider()
{
}

CircleCollider::CircleCollider(float radius, Play::Point2D pos) : m_radius(radius), m_pos(pos)
{
	
}

bool CircleCollider::collidesWith(Collider& other)
{
	// Check collision with another circle collider
	if (CircleCollider* otherCircle = dynamic_cast<CircleCollider*>(&other))
	{
		float distance = (otherCircle->m_pos - m_pos).Length();/* calculate distance between centers of the two circles */
		return distance < (m_radius + otherCircle->m_radius);
	}
	// Check collision with other types of colliders (e.g. box collider)
	else {
		// TODO: implement collision detection with other collider types
		return false;
	}
}

void CircleCollider::DrawBoundingBox(Play::Colour color )
{
	Play::DrawCircle(m_pos, m_radius, color);
	Play::DrawDebugText(m_pos, std::to_string(m_id).c_str(), color, true);
}

void CircleCollider::Init(Play::Point2D pos, float radius)
{
	m_pos = pos;
	m_radius = radius;
}

float CircleCollider::GetRadius()
{
	return m_radius;
}

