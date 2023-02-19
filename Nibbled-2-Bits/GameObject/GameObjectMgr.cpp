#include "GameObjectMgr.h"
#include <map> // map faster or vector faster ? ? ?

namespace GameObjectMgr
{
	std::map<int, GameObject*> g_gameObjectList;

	void AddNewGameObject(GameObject& obj)
	{
		g_gameObjectList[obj.m_id] = &obj;
	}

	void RemoveGameObject(GameObject& obj)
	{
		if (g_gameObjectList.find(obj.m_id) != g_gameObjectList.end())
			g_gameObjectList.erase(obj.m_id);
	}

	GameObject* GetGameObjectByid(int id)
	{
		if (g_gameObjectList.find(id) != g_gameObjectList.end())
			return g_gameObjectList[id];
	}

}

