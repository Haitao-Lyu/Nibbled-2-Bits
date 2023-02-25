#pragma once
#include <map>
#include <vector>
#include <string>
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


public:
	Level(const char* name);
	~Level();

	void render();

	void SetTileType(std::vector<std::vector<int>>& adjacentTiles);

	void CheckAjacentTiles();

	void LoadLevel();
};

