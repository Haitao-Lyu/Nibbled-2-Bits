#include "pch.h"
#include "GameObjectMgr.h"
#include <map> // map faster or vector faster ? ? ?
#include "../GameTool/DebugTool.h"
#include "../GameObject/Tube.h"
namespace GameObjectMgr
{
	std::map<int, GameObject*> g_gameObjectMapAll;

	std::map<int, std::vector<GameObject*>> g_gameObjectMapbyType;

	void AddNewGameObject(GameObject& obj)
	{
		g_gameObjectMapAll[obj.m_id] = &obj;
		g_gameObjectMapbyType[static_cast<int>(obj.m_type)].push_back(&obj);
	}

	void RemoveGameObject(GameObject& obj)
	{
		if (g_gameObjectMapAll.find(obj.m_id) != g_gameObjectMapAll.end())
		{
			g_gameObjectMapAll.erase(obj.m_id);
			
			for (int i = 0; i < g_gameObjectMapbyType[static_cast<int>(obj.m_type)].size(); i++)
			{
				GameObject* temp = g_gameObjectMapbyType[static_cast<int>(obj.m_type)][i];
				if(temp)
				if (temp->m_id == obj.m_id)
				{
					g_gameObjectMapbyType[static_cast<int>(obj.m_type)].erase(g_gameObjectMapbyType[static_cast<int>(obj.m_type)].begin() + i--);
					//delete temp; //cause porblem
				}
			}
		}

	}

	void RemoveGameObjectByid(int id)
	{
		GameObject& obj = *GetGameObjectByid(id);
		if (g_gameObjectMapAll.find(id) != g_gameObjectMapAll.end())
		{
			g_gameObjectMapAll.erase(id);
			for (int i = 0; i < g_gameObjectMapbyType[static_cast<int>(obj.m_type)].size(); i++)
			{
				GameObject* temp = g_gameObjectMapbyType[static_cast<int>(obj.m_type)][i];
				if (temp->m_id == obj.m_id)
				{
					g_gameObjectMapbyType[static_cast<int>(obj.m_type)].erase(g_gameObjectMapbyType[static_cast<int>(obj.m_type)].begin() + i--);
					//delete temp; //cause porblem
				}
			}
		}
		
	}

	void UpdateGameObjectsByType(E_OBJTYPE type)
	{
		//check how many game objects are there
		DebugValue((int)g_gameObjectMapbyType.size());
		if (g_gameObjectMapbyType.find(static_cast<int>(type)) != g_gameObjectMapbyType.end())
		{
			std::vector<GameObject*> &list = g_gameObjectMapbyType[static_cast<int>(type)];
			// [TODO] Check Why there are so many obj ? ? Is it right ? ? ? 
			//DebugValue((int)list.size());
			for (GameObject* obj: g_gameObjectMapbyType[static_cast<int>(type)])
			{
				if(obj)
				obj->Update();
			}
		}
	}

	void ClearAllGameobjects()
	{
		//delete all pointer in global list
		for (auto& [id, obj] : g_gameObjectMapAll)
		{
			delete obj;
		}

		//Two map have the same instance, so pointer point to the same object ?
		for (auto& [id, list] : g_gameObjectMapbyType)
		{
			list.clear();
		}
		//pointer is all clean, so just clear 
		g_gameObjectMapAll.clear();
		g_gameObjectMapbyType.clear();// will this clear the vector inside map as well?
	}

	GameObject* GetGameObjectByid(int id)
	{
		if (g_gameObjectMapAll.find(id) != g_gameObjectMapAll.end())
			return g_gameObjectMapAll[id];
		return nullptr;
	}

	std::vector<GameObject*>& GetGameObjectsByType(E_OBJTYPE type)
	{
		if (g_gameObjectMapbyType.find(static_cast<int>(type)) != g_gameObjectMapbyType.end())
			return g_gameObjectMapbyType[static_cast<int>(type)];
		else
			return g_gameObjectMapbyType[static_cast<int>(type)];
	}


	GameObject* MakeGameObject(E_OBJTYPE gameObjectType, Play::Point2f pos)
	{
		GameObject* obj = nullptr;
		switch (gameObjectType)
		{
		case E_OBJTYPE::E_NULL:
			break;
		case E_OBJTYPE::E_MOUSE:
			break;
		case E_OBJTYPE::E_TILE:
			break;
		case E_OBJTYPE::E_BOUNDARY:
			break;
		case E_OBJTYPE::E_MOUSETRAP:
			break;
		case E_OBJTYPE::E_CHEESE:
			break;
		case E_OBJTYPE::E_MOUSEHOLE:
			break;
		case E_OBJTYPE::E_TUBE:
		{
			Tube* tube = new Tube(pos);
			obj = tube;
			AddNewGameObject(*tube);
		}
			break;
		default:
			break;
		}
		return obj;
	}


}

