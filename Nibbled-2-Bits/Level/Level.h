#pragma once
#include <map>
#include <vector>
#include <string>
#include "../UI/Component/GridComponent.h"
#include "../UI/Panel.h"
#include "../GameTool/Timer.h"
enum class E_BACKGROUND
{
	E_BLUE,
	E_GREEEN,
	E_PURPLE,
	E_RED,
	E_WOOD,
	E_YELLOW,
};

class Level
{
private:

	const char* levelName;
	//Game object id for loading
	std::vector<std::vector<int>> m_mapinfo;
	std::vector<std::vector<int>> inventoryInfo;
	//All the panel items in level should be interactable
	Panel* m_gamePanel{ nullptr };
	Panel* m_itemPanel{ nullptr };
	Panel* m_endLevelPanel{ nullptr };
	bool isStart = false;
	bool isEnd = false;
	Timer m_timer { 0 };
public:
	int m_id = -1;
	int exitMouseNumber = 0;
	int cheeseNumber = 0;
	float levelTimeLimit = 0;

public:
	Level(const char* name);
	~Level();

	void OnEnter();

	void OnExit();

	void Update();

	void Clear();

	void Destroy();

	bool isLevelEnd();

	void AddLevelEvents();

	Panel* GetGamePanel();

	void SetTileType(std::vector<std::vector<int>>& adjacentTiles);

	void CheckAjacentTiles();

	void FromItemPanelAddToLevel(GridItem& grid, int x, int y);

	void FromLevelMoveToLevel(GridItem& grid, int x, int y);

	void CheckGamePanelEvent();

	void CheckItemPanelEvent();

	void CheckEndLevelPanelEvent();

	void LoadLevelPanel();

	void LoadLeveltoScene();
};

