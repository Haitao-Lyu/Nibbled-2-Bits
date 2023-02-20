#include "pch.h"
#include "Collider.h"

bool BoxCollider::collidesWith(const Collider& other) const
{
    // Check collision with another box collider
    if (const BoxCollider* otherBox = dynamic_cast<const BoxCollider*>(&other)) 
    {
        // TODO: implement collision detection with another box collider
        return false;
    }
    // Check collision with other types of colliders (e.g. circle collider)
    else
    {
        // TODO: implement collision detection with other collider types
        return false;
    }
}

bool CircleCollider::collidesWith(const Collider& other) const
{
    // Check collision with another circle collider
    if (const CircleCollider* otherCircle = static_cast<const CircleCollider*>(&other)) 
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
