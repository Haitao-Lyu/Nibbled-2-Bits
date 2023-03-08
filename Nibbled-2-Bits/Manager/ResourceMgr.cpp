#include "pch.h"
#include "ResourceMgr.h"
#include "../MainGame.h"
#include <vector>
#include "../GameTool/DebugTool.h"
#include "../GameTool/Math2D.h"

const char* C_FONT_ABNORMAL_40 = "font_ABNORMAL40px_10x10";
const char* C_FONT_BOLD_64 = "font64px_10x10";
const char* C_FONT_LIGHT_64 = "fontui64px_10x10";

const char* C_BK_BLUE = "bk_blue";
const char* C_BK_GREEN = "bk_green";
const char* C_BK_PURPLE = "bk_purple";
const char* C_BK_RED = "bk_red";
const char* C_BK_YELLOW = "bk_yellow";
const char* C_BK_WOOD = "bk_wood";

//inventory info
// Postition 0 - Tube two way || 2 - tube 3 way|| 1 - tube 1 way  
static std::vector<int> lev1{ 1,0,0,0 };
static std::vector<int> lev2{ 2,0,0,0 };
static std::vector<int> lev3{ 2,0,0,0 };

static const std::vector<std::vector<int>> levelInventoryList{ lev1,lev2,lev3 };


const int GRID_WIDTH = 16;
const int GRID_HEIGHT = 14;
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
		const Play::Matrix2D scaleMt = Play::Matrix2D(
			{ static_cast<float>(DISPLAY_HEIGHT) / static_cast<float>(Play::GetSpriteHeight(spriteName)) + 0.1f ,0.0f,0.0f },
			{ 0.0f,static_cast<float>(DISPLAY_WIDTH) / static_cast<float>(Play::GetSpriteWidth(spriteName)) ,0.0f },
			{ static_cast<float>(DISPLAY_WIDTH / 2),DISPLAY_HEIGHT - static_cast<float>(DISPLAY_HEIGHT / 2),0.0f });
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

GameAreaInfo& ResoureMgr::LoadLevel(std::string levelName)
{

	std::ifstream levelFile;

	GameAreaInfo* gameAreaInfo = new GameAreaInfo(GRID_WIDTH,GRID_HEIGHT);

	/// <summary>
	/// WHY DONT JUST SAVE POSITION WHY SAVE INDEX ? ? ? ? ? 
	/// </summary>
	/// <param name="levelName"></param>
	/// <returns></returns>

	levelFile.open("data\\" + levelName + ".lev");
	//Do nothing if the file does not exist
	if (levelFile.fail()) 
	{
		PLAY_ASSERT_MSG(levelFile.fail(), "LEVEL NAME IS INVALID");
		return *gameAreaInfo;
	}


	std::string object;
	//Ignore first line
	std::getline(levelFile, object);

	//Read the next 2 lines as the mouse hole positions
	std::getline(levelFile, object);
	std::istringstream ss1{ object };
	std::string token1;
	std::vector<std::string> tokens1;
	while (std::getline(ss1, token1, ',')) {
		tokens1.push_back(token1);
	}
	//Mouse Hole Entry
	gameAreaInfo->EntryPos.x = static_cast<float>(stoi(tokens1[0]) + 1);
	gameAreaInfo->EntryPos.y = static_cast<float>((GRID_HEIGHT - 1)  - stoi(tokens1[1]));

	//Read the next 2 lines as the mouse hole positions
	std::getline(levelFile, object);
	ss1 = std::istringstream{ object };
	tokens1.clear();
	while (std::getline(ss1, token1, ',')) {
		tokens1.push_back(token1);
	}
	//Mouse Hole Exit
	gameAreaInfo->ExitPos.x = static_cast<float>(stoi(tokens1[0]) + 1);
	gameAreaInfo->ExitPos.y = static_cast<float>((GRID_HEIGHT - 1)  -stoi(tokens1[1]));

	while (!levelFile.eof()) {
		std::getline(levelFile, object);
		if (object == "") continue; // ignore empty lines
		if (object == "Inventory") break; //Stop if we reach the inventory part of the save file

		//Create a vector of strings from the comma seperated variables
		std::istringstream ss{ object };
		std::string token;
		std::vector<std::string> tokens;

		while (std::getline(ss, token, ',')) {
			tokens.push_back(token);
		}

		GameAreaObject* tmpObject = new GameAreaObject();
		//check game object type
		std::string s_type = tokens[0];
		if (std::strcmp(s_type.c_str(), "single ") == 0)
		{
			tmpObject->m_type = E_OBJTYPE::E_TILE;
		}
		else if (std::strcmp(s_type.c_str(), "Mouse") == 0)
		{
			tmpObject->m_type = E_OBJTYPE::E_MOUSE;
			tmpObject->m_color = 0;//grey
		}
		else if (std::strcmp(s_type.c_str(), "Mouse_dark_grey") == 0)
		{
			tmpObject->m_type = E_OBJTYPE::E_MOUSE;
			tmpObject->m_color = 1;//dark_grey
		}
		else if (std::strcmp(s_type.c_str(), "white_walk_") == 0)//MOUSE
		{
			tmpObject->m_type = E_OBJTYPE::E_MOUSE;
			tmpObject->m_color = 2;//white
		}
		else if (std::strcmp(s_type.c_str(), "trap_light") == 0)
		{
			tmpObject->m_type = E_OBJTYPE::E_MOUSETRAP;
			tmpObject->trap_color = false;
		}
		else if (std::strcmp(s_type.c_str(), "trap_dark") == 0)
		{
			tmpObject->m_type = E_OBJTYPE::E_MOUSETRAP;
			tmpObject->trap_color = true;
		}
		else if (std::strcmp(s_type.c_str(), "cheese") == 0)
		{
			tmpObject->m_type = E_OBJTYPE::E_CHEESE;
		}
		else if (std::strcmp(s_type.c_str(), "tube_one_way ") == 0)
		{
			tmpObject->m_type = E_OBJTYPE::E_TUBE;
			tmpObject->tubeType = 0;
		}
		else if (std::strcmp(s_type.c_str(), "tube_two_way ") == 0)
		{
			tmpObject->m_type = E_OBJTYPE::E_TUBE;
			tmpObject->tubeType = 1;
		}
		else if (std::strcmp(s_type.c_str(), "tube_three_way ") == 0)
		{
			tmpObject->m_type = E_OBJTYPE::E_TUBE;
			tmpObject->tubeType = 2;
		}
		tmpObject->posx = stoi(tokens[1]);
		tmpObject->posy = (GRID_HEIGHT - 1) - stoi(tokens[2]);
		tmpObject->rot = stoi(tokens[3]);
		tmpObject->misc = stoi(tokens[4]);
		gameAreaInfo->objects[tmpObject->posx][ tmpObject->posy] = tmpObject;
		//tokens.clear();
	}

	//print debug info
	//for (std::vector<GameAreaObject*>& col : gameAreaInfo->objects)
	//{
	//	for (GameAreaObject* item : col)
	//	{
	//		if (item)
	//			logDebugInfo(std::to_string((int)(item->m_type)) + " " + std::to_string(item->posx) + " " + std::to_string(item->posy) , "debug.log");
	//		else
	//			logDebugInfo("nullptr", "debug.log");
	//	}
	//	logDebugInfo("\n");
	//}

	levelFile.close();

	return *gameAreaInfo;

}

const char* ResoureMgr::GetFontName(E_FONTS font)
{
	switch (font)
	{
	case E_FONTS::ABNORMAL_40:
		return C_FONT_ABNORMAL_40;
		break;
	case E_FONTS::BOLD_64:
		return C_FONT_BOLD_64;
		break;
	case E_FONTS::LIGHT_64:
		return C_FONT_LIGHT_64;
		break;
	default:
		break;
	}
}

std::vector<int> ResoureMgr::LoadLevelPanelInfo(int levelIndex)
{
		return levelInventoryList[levelIndex];
}

void GameAreaInfo::Destory()
{
	for (std::vector<GameAreaObject*>& list : objects)
	{
		for (GameAreaObject* obj : list)
		{
			delete obj;
		}
		list.clear();//Will clear function handle the pointer ? ? ? // Or always manually delete
	}
	objects.clear();
}
