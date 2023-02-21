#pragma once
#include "GameObject.h"


namespace GameObjectMgr
{
	void AddNewGameObject(GameObject& obj);

	void RemoveGameObject(GameObject& obj);

	void RemoveGameObjectByid(int id);

	void UpdateGameObjectsByType(E_OBJTYPE TYPE);

	GameObject* GetGameObjectByid(int id);

	std::vector<GameObject*>& GetGameObjectsByType(E_OBJTYPE type);
}

