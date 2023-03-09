#include "pch.h"
#include "LevelMgr.h"

LevelMgr* LevelMgr::_instance;

LevelMgr::LevelMgr()
{

}

LevelMgr* LevelMgr::GetInstance()
{
	if (_instance)
	{
		return _instance;
	}
	return _instance = new LevelMgr();
}

void LevelMgr::Clear()
{
	//Each Time Only Load One Level
	if(currentLevel)
	currentLevel->Clear();
	//clear all level, reset current level index
	currentLevel = nullptr;
	currentLevelIndex = 0;

	level_list.clear();
}

void LevelMgr::ClearCurrentLevel()
{
	currentLevel->Clear();
	currentLevel = nullptr;
	currentLevelIndex = 0;
}

Level* LevelMgr::GetLevel(int i)
{
	if(i < level_list.size())
		return level_list[i];
	return nullptr;
}

void LevelMgr::Update()
{
	if(currentLevel)
		currentLevel->Update();

	Level* newLevel = nullptr;
	if (currentLevel)
	{
		if (currentLevel->isLevelEnd())
		{
			newLevel = level_list[currentLevelIndex++];
		}
	}
	else
	{
		// ? ? ? ? ? ? ? 
		//Get The pointer of the vector , when delete one, all the element in list is deleted
		//currentLevel = &level_list[currentLevelIndex++]; 
		// -> Pointer Won't change, But item in list will shift for any reason -> cause runtime bug
		// ? ? ? ? ? ? ? ? 
		//Enter First Level
		currentLevel = level_list[currentLevelIndex++];
		currentLevel->OnEnter();
	}

	//Check If Level has Changed,call enter and exit function
	if (newLevel != nullptr)
	{
		currentLevel->OnExit();
		delete currentLevel;
		currentLevel = newLevel;
		currentLevel->OnEnter();
	}
}

void LevelMgr::AddNewLevel(const char* name)
{
	Level* level = new Level(name);
	level_list.push_back(level);
	level->m_id = level_list.size() - 1;
	MaxLevelNumber = level_list.size();
}

Level* LevelMgr::GetCurrentLevel()
{
	return currentLevel;
}

LevelMgr::~LevelMgr()
{
	for (auto& lev : level_list)
	{
		if (lev)
			delete lev;
	}
}

