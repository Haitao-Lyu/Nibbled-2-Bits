#include "pch.h"
#include "Collider.h"
#include "CollisionSystem.h"

int Collider::id = 0;

Collider::Collider()
{
	m_id = id;
	id++;
}

Collider::Collider(Play::Point2D pos)
{
    m_pos = pos;
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
