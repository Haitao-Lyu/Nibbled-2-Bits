#include "pch.h"
#include "GameObjectMgr.h"
#include <map> // map faster or vector faster ? ? ?
#include "Mouse.h"
#include "../GameTool/DebugTool.h"
namespace GameObjectMgr
{
	std::map<int, GameObject*> g_gameObjectListAll;

	std::map<int, std::vector<GameObject*>> g_gameObjectLisbyType;

	void AddNewGameObject(GameObject& obj)
	{
		g_gameObjectListAll[obj.m_id] = &obj;
		g_gameObjectLisbyType[static_cast<int>(obj.m_type)].push_back(&obj);
	}

	void RemoveGameObject(GameObject& obj)
	{
		if (g_gameObjectListAll.find(obj.m_id) != g_gameObjectListAll.end())
		{
			g_gameObjectListAll.erase(obj.m_id);
			
			for (int i = 0; i < g_gameObjectLisbyType[static_cast<int>(obj.m_type)].size(); i++)
			{
				GameObject* temp = g_gameObjectLisbyType[static_cast<int>(obj.m_type)][i];
				if (temp->m_id == obj.m_id)
				{
					g_gameObjectLisbyType[static_cast<int>(obj.m_type)].erase(g_gameObjectLisbyType[static_cast<int>(obj.m_type)].begin() + i--);
				}
			}
		}

	}

	void RemoveGameObjectByid(int id)
	{
		GameObject& obj = *GetGameObjectByid(id);
		if (g_gameObjectListAll.find(id) != g_gameObjectListAll.end())
		{
			g_gameObjectListAll.erase(id);
			for (int i = 0; i < g_gameObjectLisbyType[static_cast<int>(obj.m_type)].size(); i++)
			{
				GameObject* temp = g_gameObjectLisbyType[static_cast<int>(obj.m_type)][i];
				if (temp->m_id == obj.m_id)
				{
					g_gameObjectLisbyType[static_cast<int>(obj.m_type)].erase(g_gameObjectLisbyType[static_cast<int>(obj.m_type)].begin() + i--);
				}
			}
		}
		
	}

	void UpdateGameObjectsByType(E_OBJTYPE type)
	{
		DebugValue((int)g_gameObjectLisbyType.size());
		if (g_gameObjectLisbyType.find(static_cast<int>(type)) != g_gameObjectLisbyType.end())
		{
			std::vector<GameObject*>& list = g_gameObjectLisbyType[static_cast<int>(type)];
			// [TODO] Check Why there are so many obj ? ? Is it right ? ? ? 
			//DebugValue((int)list.size());
			for (GameObject* obj: g_gameObjectLisbyType[static_cast<int>(type)])
			{
				obj->Update();
			}
		}
	}

	GameObject* GetGameObjectByid(int id)
	{
		if (g_gameObjectListAll.find(id) != g_gameObjectListAll.end())
			return g_gameObjectListAll[id];
		return nullptr;
	}

	std::vector<GameObject*>& GetGameObjectsByType(E_OBJTYPE type)
	{
		if(g_gameObjectLisbyType.find(static_cast<int>(type)) != g_gameObjectLisbyType.end())
		return g_gameObjectLisbyType[static_cast<int>(type)];
	}

}

