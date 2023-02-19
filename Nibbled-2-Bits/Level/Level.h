#pragma once
#include <map>
#include <vector>
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
	//Gameobject id for loading
	std::vector<std::vector<int>> m_mapinfo;
public:
	Level();
	~Level();

	void render();

	void SetTileType(std::vector<std::vector<int>>& adjacentTiles);

	void CheckAjacentTiles();

};

