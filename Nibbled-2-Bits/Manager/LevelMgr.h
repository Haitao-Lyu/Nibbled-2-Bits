#pragma once
#include "../Level/level.h"
class LevelMgr
{
private:
	std::vector<Level*> level_list;

	int MaxLevelNumber = 0;

	int currentLevelIndex = 0;

	Level* currentLevel = nullptr;

	static LevelMgr* _instance;

private:

	LevelMgr();

	LevelMgr(const LevelMgr &levelMgr) = delete;

	const LevelMgr& operator==(const LevelMgr& levelMgr) = delete;

public:

	static LevelMgr* GetInstance();

	void AddNewLevel(const char* name);

	Level* GetCurrentLevel();

	void Clear();

	void ClearCurrentLevel();

	Level* GetLevel(int i);

	void Update();

	~LevelMgr();
};

