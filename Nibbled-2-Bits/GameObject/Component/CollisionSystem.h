#pragma once
#include <vector>
#include "Collider.h"


namespace CollisionSystem
{
	void AddNewCollider(Collider* collider);

	void UpdateCollision();

	void UpdateCollisionByCollider(Collider* collider);
}