#include "pch.h"
#include "CollisionSystem.h"

namespace CollisionSystem
{
	static std::vector<Collider*> g_colliders;

	void AddNewCollider(Collider* collider)
	{
		g_colliders.push_back(collider);
	}


	void UpdateCollision()
	{
		for (Collider* collider1:g_colliders)
		{
			for (Collider* collider2: g_colliders)
			{
				if(*collider1 == *collider2)
					continue;
				collider1->collidesWith(*collider2);
			}
		}
	}

	void UpdateCollisionByCollider(Collider* collider)
	{
		for (Collider* other : g_colliders)
		{
			collider->collidesWith(*other);
		}
	}

}
