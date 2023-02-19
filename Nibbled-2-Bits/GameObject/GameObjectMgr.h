#pragma once
#include "GameObject.h"


namespace GameObjectMgr
{
	void AddNewGameObject(GameObject& obj);

	void RemoveGameObject(GameObject& obj);

	GameObject* GetGameObjectByid(int id);
}

