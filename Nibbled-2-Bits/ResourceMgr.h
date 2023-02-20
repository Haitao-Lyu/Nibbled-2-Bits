#pragma once
#include "pch.h"
#include "GameObject/GameObjectMgr.h"
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
};

namespace ResoureMgr
{
	void DrawBackground(E_BKCOLOR COLOR = E_BKCOLOR::WOOD, E_BKMODE MODE = E_BKMODE::FILL);

	std::vector<std::vector<GameAreaObject*>>& LoadLevel(std::string levelName);
};