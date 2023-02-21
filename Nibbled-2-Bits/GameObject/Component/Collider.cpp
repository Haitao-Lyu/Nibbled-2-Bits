#include "pch.h"
#include "Collider.h"
#include "CollisionSystem.h"

int Collider::id = 0;

Collider::Collider()
{
    m_id = id;
	id++;
}

int Collider::Getid()
{
    return m_id;
}

bool Collider::operator==(Collider& colldier) const
{
    if (m_id == colldier.m_id)
    {
        return true;
    }
    return false;
}

BoxCollider::BoxCollider()
{
}

BoxCollider::BoxCollider(float width, float height, Play::Point2D pos, GameObject* info) : m_width(width), m_height(height), m_pos(pos)
{
	lt = { m_pos.x - m_width / 2,m_pos.y - m_height / 2 };
	lb = { m_pos.x - m_width / 2,m_pos.y + m_height / 2 };
	rt = { m_pos.x + m_width / 2,m_pos.y - m_height / 2 };
	rb = { m_pos.x + m_width / 2,m_pos.y + m_height / 2 };
    m_holderInfo = info;
    CollisionSystem::AddNewCollider(this);
}

void BoxCollider::Init(float width, float height, Play::Point2D pos, GameObject* info)
{
    m_width = width; 
    m_height = height; 
    m_pos = pos;
	lt = { m_pos.x - m_width / 2,m_pos.y - m_height / 2 };
	lb = { m_pos.x - m_width / 2,m_pos.y + m_height / 2 };
	rt = { m_pos.x + m_width / 2,m_pos.y - m_height / 2 };
	rb = { m_pos.x + m_width / 2,m_pos.y + m_height / 2 };
    m_holderInfo = info;
}

void BoxCollider::UpdateShape(float width, float height, Play::Point2D pos)
{
	m_width = width;
	m_height = height;
	m_pos = pos;
	lt = { m_pos.x - m_width / 2,m_pos.y - m_height / 2 };
	lb = { m_pos.x - m_width / 2,m_pos.y + m_height / 2 };
	rt = { m_pos.x + m_width / 2,m_pos.y - m_height / 2 };
	rb = { m_pos.x + m_width / 2,m_pos.y + m_height / 2 };
}

bool BoxCollider::collidesWith( Collider& other) 
{
    // Check collision with another box collider
    if ( BoxCollider* otherBox = dynamic_cast< BoxCollider*>(&other)) 
    {
        if (otherBox->lt.x > lt.x && otherBox->lt.x < rb.x && otherBox->lt.y > lt.y && otherBox->lt.y  < rb.y)
        {
           // m_opponentInfo = otherBox->m_holderInfo;
            return true;
        }
		else if (otherBox->rt.x > lt.x && otherBox->rt.x < rb.x && otherBox->rt.y > lt.y && otherBox->rt.y < rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		else if (otherBox->lb.x > lt.x && otherBox->lb.x < rb.x && otherBox->lb.y > lt.y && otherBox->lb.y < rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
		else if (otherBox->rb.x > lt.x && otherBox->rb.x < rb.x && otherBox->rb.y > lt.y && otherBox->rb.y < rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
        ///check if this box point is in the other box
        else if (lt.x > otherBox->lt.x && lt.x < otherBox->rb.x && lt.y > otherBox->lt.y && lt.y < otherBox->rb.y)
		{
			// m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
        else if (rt.x > otherBox->lt.x && rt.x < otherBox->rb.x && rt.y > otherBox->lt.y && rt.y < otherBox->rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
        else if (lb.x > otherBox->lt.x && lb.x < otherBox->rb.x && lb.y > otherBox->lt.y && lb.y < otherBox->rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
        else if (rb.x > otherBox->lt.x && rb.x < otherBox->rb.x && rb.y > otherBox->lt.y && rb.y < otherBox->rb.y)
		{
			//m_opponentInfo = otherBox->m_holderInfo;
			return true;
		}
        else
		// m_opponentInfo = nullptr;
        return false;
    }
    // Check collision with other types of colliders (e.g. circle collider)
    else
    {
        // TODO: implement collision detection with other collider types
        return false;
    }
}

void BoxCollider::DrawBoundingBox()
{
    Play::DrawRect(lt, rb, Play::cRed);
    Play::DrawDebugText(m_pos, std::to_string(m_id).c_str(), Play::cRed,true);
}

void BoxCollider::OnCollision(std::function<void()> fun)
{
    if (m_opponentInfo != nullptr)
    {
        fun();
    }
}

float BoxCollider::GetWidth()
{
    return m_width;
}

float BoxCollider::GetHeight()
{
    return m_height;
}

CircleCollider::CircleCollider(float radius, Play::Point2D pos) : m_radius(radius), m_pos(pos) 
{
    CollisionSystem::AddNewCollider(this);
}

bool CircleCollider::collidesWith( Collider& other) 
{
    // Check collision with another circle collider
    if ( CircleCollider* otherCircle = dynamic_cast< CircleCollider*>(&other))
    {
        float distance = 1.0f/* calculate distance between centers of the two circles */;
        return distance < (m_radius + otherCircle->m_radius);
    }
    // Check collision with other types of colliders (e.g. box collider)
    else {
        // TODO: implement collision detection with other collider types
        return false;
    }
}

