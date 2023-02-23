#include "pch.h"
#include "ResourceMgr.h"
#include "MainGame.h"
#include <vector>
#include "GameTool/DebugTool.h"
#include "GameTool/Math2D.h"
const char* C_FONT_ABNORMAL_40 = "font_ABNORMAL40px_10x10";
const char* C_FONT_BOLD_64 = "font64px_10x10";
const char* C_FONT_LIGHT_64 = "fontui64px_10x10";

const char* C_BK_BLUE = "bk_blue";
const char* C_BK_GREEN = "bk_green";
const char* C_BK_PURPLE = "bk_purple";
const char* C_BK_RED = "bk_red";
const char* C_BK_YELLOW = "bk_yellow";
const char* C_BK_WOOD = "bk_wood";


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

	static GameAreaInfo gameAreaInfo(GRID_WIDTH,GRID_HEIGHT);

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
		return gameAreaInfo;
	}


	std::string object;
	//Ignore first line
	std::getline(levelFile, object);

	//Read the next 2 lines as the mouse hole positions
	std::getline(levelFile, object);
	std::istringstream ss{ object };
	std::string token;
	std::vector<std::string> tokens;
	while (std::getline(ss, token, ',')) {
		tokens.push_back(token);
	}
	//Mouse Hole Entry
	gameAreaInfo.EntryPos.x = stoi(tokens[0]) + 1;
	gameAreaInfo.EntryPos.y = (GRID_HEIGHT - 1)  - stoi(tokens[1]);

	//Read the next 2 lines as the mouse hole positions
	std::getline(levelFile, object);
	ss = std::istringstream{ object };
	tokens.clear();
	while (std::getline(ss, token, ',')) {
		tokens.push_back(token);
	}
	//Mouse Hole Exit
	gameAreaInfo.ExitPos.x = stoi(tokens[0]) + 1;
	gameAreaInfo.ExitPos.y = (GRID_HEIGHT - 1)  -stoi(tokens[1]);

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
		tmpObject->posx = stoi(tokens[1]);
		tmpObject->posy = (GRID_HEIGHT - 1) - stoi(tokens[2]);
		tmpObject->rot = stoi(tokens[3]);
		tmpObject->misc = stoi(tokens[4]);
		gameAreaInfo.objects[tmpObject->posx][ tmpObject->posy] = tmpObject;
		//tokens.clear();
	}

	//debug
	for (std::vector<GameAreaObject*>& col : gameAreaInfo.objects)
	{
		for (GameAreaObject* item : col)
		{
			if (item)
				logDebugInfo(std::to_string((int)(item->m_type)) + " " + std::to_string(item->posx) + " " + std::to_string(item->posy) , "debug.log");
			else
				logDebugInfo("nullptr", "debug.log");
		}
		logDebugInfo("\n");
	}
	//std::vector<std::tuple<int, int>> playerInventory;

	//while (!levelFile.eof()) {
	//	std::getline(levelFile, object);
	//	if (object == "") continue; // ignore empty lines

	//	std::istringstream ss{ object };
	//	std::string token;
	//	std::vector<std::string> tokens;

	//	while (std::getline(ss, token, ',')) {
	//		tokens.push_back(token);
	//	}

	//	playerInventory.push_back({ idMap[tokens[0]], stoi(tokens[1]) });
	//}

	//m_panel.SetPlayerInventory(playerInventory);

	levelFile.close();

	return gameAreaInfo;
	//m_gameArea.SetGameAreaObjects(objects);

	//m_gameArea.m_lastSelected = { -1,-1 };
}

