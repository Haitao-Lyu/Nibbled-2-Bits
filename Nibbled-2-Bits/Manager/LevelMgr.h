#pragma once
#include "../Level/level.h"
class LevelMgr
{
private:
	std::vector<Level> level_list;
private:
	static LevelMgr* _instance;

	LevelMgr();

	LevelMgr(const LevelMgr &levelMgr) = delete;

	const LevelMgr& operator==(const LevelMgr& levelMgr) = delete;

public:

	static LevelMgr* GetInstance();

	void AddNewLevel(const char* name);

	void Destroy();

	Level* GetLevel(int i);

	~LevelMgr();
};

