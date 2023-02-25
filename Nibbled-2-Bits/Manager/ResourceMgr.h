#pragma once
#include "GameObjectMgr.h"
#include <string>
enum class E_BKCOLOR
{
	GREEN,
	BLUE,
	PURPLE,
	RED,
	YELLOW,
	WOOD
};

enum class E_BKMODE
{
	FILL,
	CENTER,
	FIT
};

enum class E_FONTS
{
	ABNORMAL_40,
	BOLD_64,
	LIGHT_64,
};

struct GameAreaObject {
	E_OBJTYPE m_type{ -1 };
	int posx{ 0 };
	int posy{ 0 };
	int rot{ 0 };
	int misc{ 0 };
	bool mouseHole{ false };
	bool vis{ true };
	bool trap_color{true};//true for dark
	short m_color = 0;
};

struct GameAreaInfo
{
	Play::Point2D EntryPos{ 0.0f, 0.0f };
	Play::Point2D ExitPos { 0.0f, 0.0f };
	std::vector<std::vector<GameAreaObject*>>  objects;

	GameAreaInfo(int row_num, int col_num):objects(row_num, std::vector<GameAreaObject*>(col_num))
	{
		
	}
};

namespace ResoureMgr
{
	void DrawBackground(E_BKCOLOR COLOR = E_BKCOLOR::WOOD, E_BKMODE MODE = E_BKMODE::FILL);

	GameAreaInfo& LoadLevel(std::string levelName);
};