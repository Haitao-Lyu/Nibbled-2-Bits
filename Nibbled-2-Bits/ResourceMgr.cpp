#include "ResourceMgr.h"

#include "MainGame.h"

const char* C_FONT_ABNORMAL_40 = "font_ABNORMAL40px_10x10";
const char* C_FONT_BOLD_64 = "font64px_10x10";
const char* C_FONT_LIGHT_64 = "fontui64px_10x10";

const char* C_BK_BLUE = "bk_blue";
const char* C_BK_GREEN = "bk_green";
const char* C_BK_PURPLE = "bk_purple";
const char* C_BK_RED = "bk_red";
const char* C_BK_YELLOW = "bk_yellow";
const char* C_BK_WOOD = "bk_wood";

void ResoureMgr::DrawBackground(E_BKCOLOR COLOR, E_BKMODE MODE)
{
	const char* spriteName = "";
	switch (COLOR)
	{
	case E_BKCOLOR::GREEN:
		spriteName = C_BK_GREEN;
		break;
	case E_BKCOLOR::BLUE:
		spriteName = C_BK_BLUE;
		break;
	case E_BKCOLOR::PURPLE:
		spriteName = C_BK_PURPLE;
		break;
	case E_BKCOLOR::RED:
		spriteName = C_BK_RED;
		break;
	case E_BKCOLOR::YELLOW:
		spriteName = C_BK_YELLOW;
		break;
	case E_BKCOLOR::WOOD:
		spriteName = C_BK_WOOD;
		break;
	}

	switch (MODE)
	{
	case E_BKMODE::FILL:
	{
		Play::Matrix2D scaleMt = Play::Matrix2D(
			{ static_cast<float>(DISPLAY_HEIGHT) / static_cast<float>(Play::GetSpriteHeight(spriteName)) + 0.1f ,0.0f,0.0f },
			{ 0.0f,static_cast<float>(DISPLAY_WIDTH) / static_cast<float>(Play::GetSpriteWidth(spriteName)) ,0.0f },
			{ static_cast<float>(DISPLAY_WIDTH / 2),static_cast<float>(DISPLAY_HEIGHT / 2),0.0f });
		Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt, 0);
		break;
	}
	case E_BKMODE::CENTER:
		Play::DrawSprite(spriteName, { DISPLAY_HEIGHT / 2,DISPLAY_WIDTH / 2 }, 0);
		break;
	case E_BKMODE::FIT:
		Play::DrawSprite(spriteName, { DISPLAY_HEIGHT / 2,DISPLAY_WIDTH / 2 }, 0);
		break;
	}
}

