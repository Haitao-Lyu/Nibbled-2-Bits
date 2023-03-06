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

void LevelMgr::Destroy()
{
	delete _instance;
}

Level* LevelMgr::GetLevel(int i)
{
	if(i < level_list.size())
		return &level_list[i];
	return nullptr;
}

void LevelMgr::AddNewLevel(const char* name)
{
	Level level(name);
	level_list.push_back(level);
}

LevelMgr::~LevelMgr()
{
	delete _instance;
}

