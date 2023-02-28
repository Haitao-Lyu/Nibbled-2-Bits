#pragma once
#include <map>
#include <vector>
#include <string>
#include "../UI/Component/GridComponent.h"
#include "../UI/Panel.h"
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

	//All the panel items in level should be interactable
	Panel* m_gamePanel;
	Panel* m_itemPanel;

public:
	Level(const char* name);
	~Level();

	void Update();

	void SetTileType(std::vector<std::vector<int>>& adjacentTiles);

	void CheckAjacentTiles();

	void FromItemPanelAddToLevel(GridItem& grid, short x, short y);

	void FromLevelMoveToLevel(GridItem& grid, short x, short y);

	void LevelControl();

	void CheckPanelEvent();

	void LoadLevelPanel();

	void LoadLevel_Old();

	void LoadLevelBaseOnGrid();
};

