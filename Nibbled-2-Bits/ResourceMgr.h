#pragma once
#include "PlayCustom.h"
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

namespace ResoureMgr
{
	void DrawBackground(E_BKCOLOR COLOR = E_BKCOLOR::WOOD, E_BKMODE MODE = E_BKMODE::FILL);
};