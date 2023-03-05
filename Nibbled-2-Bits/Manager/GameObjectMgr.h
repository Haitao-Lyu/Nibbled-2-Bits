#pragma once
#include "../GameObject/GameObject.h"


namespace GameObjectMgr
{
	void AddNewGameObject(GameObject& obj);

	void RemoveGameObject(GameObject& obj);

	void RemoveGameObjectByid(int id);

	void UpdateGameObjectsByType(E_OBJTYPE TYPE);

	void ClearAllGameobjects();

	GameObject* MakeGameObject(E_OBJTYPE gameObjectType, Play::Point2f pos);

	GameObject* GetGameObjectByid(int id);

	std::vector<GameObject*>& GetGameObjectsByType(E_OBJTYPE type);
}

