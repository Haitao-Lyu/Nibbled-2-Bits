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
	std::vector<int> m_map;
public:
	Level();
	~Level();

	void render();

};

