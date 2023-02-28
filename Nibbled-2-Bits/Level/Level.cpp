#include "pch.h"
#include "Level.h"
#include "../Manager/ResourceMgr.h"
#include "../Manager/GameObjectMgr.h"
#include "../MainGame.h"

#include "../GameObject/Tile.h"
#include "../GameObject/Mouse.h"
#include "../GameObject/Boundary.h"
#include "../GameObject/MouseTrap.h"
#include "../GameObject/Cheese.h"
#include "../GameObject/MouseHole.h"

//from mouse editor
Play::Point2D GameToWorld(Play::Point2D pos) {
	Play::Point2D botLeftGrid{ DISPLAY_WIDTH - GAME_AREA_WIDTH + 25, DISPLAY_HEIGHT - GAME_AREA_HEIGHT };
	return pos + botLeftGrid;
}

Level::Level(const char* name)
{
    m_mapinfo.resize(GRID_COL);
	for (std::vector<int>& row : m_mapinfo)
	{
		row.resize(GRID_ROW);
	}
	levelName = name;
	gridComponent.InitGridInfo(GRID_ROW + 2, GRID_COL + 2, GAME_AREA_HEIGHT + 1, GAME_AREA_WIDTH - 50, {GAME_AREA_WIDTH, DISPLAY_HEIGHT/2 });
}

Level::~Level()
{

}

void Level::Update()
{
	
	Render();
}

void Level::Render()
{
	gridComponent.Render();
}

void Level::SetTileType(std::vector<std::vector<int>>& adjacentTiles)
{
    if (adjacentTiles[0][1])
    {
        
    }

}

void Level::CheckAjacentTiles()
{
    std::vector<std::vector<int>> adjacentTiles{ {0,0,0} ,{0,0,0}, {0,0,0} };
    for (int x = 0; x < m_mapinfo.size(); x++)
    {
        for (int y = 0; y < m_mapinfo[0].size(); y++)
        {
            GameObject* obj = GameObjectMgr::GetGameObjectByid(m_mapinfo[x][y]);
            if (obj->m_type == E_OBJTYPE::E_TILE)
            {
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        // skip current position and out-of-bounds positions
                        if (i == 0 && j == 0) {
                            continue;
                        }
                        if (x + i < 0 || x + i >= m_mapinfo.size() || y + j < 0 || y + j >= m_mapinfo[0].size()) {
                            continue;
                        }

                        // check if adjacent tile exists
                        GameObject* aj_obj = GameObjectMgr::GetGameObjectByid(m_mapinfo[x + i][y + j]);
                        if (aj_obj->m_type == E_OBJTYPE::E_TILE) {
                            adjacentTiles[i + 1][j + 1] = 1;
                        }
                    }
                }
            }
        }
    }
}



void Level::LoadLevelBaseOnGrid()
{
	GameAreaInfo& gameAreaInfo = ResoureMgr::LoadLevel(levelName);
	// col:16  row: 13
	std::vector<std::vector<GameAreaObject*>>& level = gameAreaInfo.objects;

	//*Create Mouse Hole*//
	MouseHole* mouse_entry = nullptr;
	if (gameAreaInfo.EntryPos.x == 0)
	{
		mouse_entry = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.EntryPos.x, gameAreaInfo.EntryPos.y), E_MOUSEHOLE_DIR::LEFT);
	}
	else if (gameAreaInfo.EntryPos.x == (GRID_COL + 1))
	{
		mouse_entry = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.EntryPos.x, gameAreaInfo.EntryPos.y), E_MOUSEHOLE_DIR::RIGHT);
	}
	else if (gameAreaInfo.EntryPos.y == 0)
	{
		mouse_entry = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.EntryPos.x, gameAreaInfo.EntryPos.y), E_MOUSEHOLE_DIR::TOP);
	}
	else if (gameAreaInfo.EntryPos.y == GRID_ROW + 1)
	{
		mouse_entry = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.EntryPos.x, gameAreaInfo.EntryPos.y), E_MOUSEHOLE_DIR::BOTTOM);
	}
	if (mouse_entry)
		GameObjectMgr::AddNewGameObject(*mouse_entry);

	Play::Point2D pos2{ gameAreaInfo.ExitPos.x * GRID_SIZE + GRID_SIZE / 2 - GRID_SIZE, gameAreaInfo.ExitPos.y * GRID_SIZE + GRID_SIZE / 2 };
	MouseHole* mouse_Exit = nullptr;
	if (gameAreaInfo.ExitPos.x == -1)
	{
		mouse_Exit = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.ExitPos.x, gameAreaInfo.ExitPos.y), E_MOUSEHOLE_DIR::LEFT);
	}
	else if (gameAreaInfo.ExitPos.x == (GRID_COL + 1))
	{
		mouse_Exit = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.ExitPos.x, gameAreaInfo.ExitPos.y), E_MOUSEHOLE_DIR::RIGHT);
	}
	else if (gameAreaInfo.ExitPos.y == 0)
	{
		mouse_Exit = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.ExitPos.x, gameAreaInfo.ExitPos.y), E_MOUSEHOLE_DIR::TOP);
	}
	else if (gameAreaInfo.ExitPos.y == GRID_ROW + 1)
	{
		mouse_Exit = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.ExitPos.x, gameAreaInfo.ExitPos.y), E_MOUSEHOLE_DIR::BOTTOM);
	}
	if (mouse_Exit)
	{
		mouse_Exit->SetType(E_MOUSEHOLE_TYPE::EXIT);
	}
	GameObjectMgr::AddNewGameObject(*mouse_Exit);

	///*create boundary outside game area*//
	//add TOP column
	for (int j = 0; j < GRID_COL + 1; j++)
	{
		Boundary* boundary = new Boundary(gridComponent.GetGridPos(j,0));
		boundary->SetDirection(E_DIR_BOUNDARY::UP);
		//set corner
		if (j == 0)
			boundary->SetCorner();
		GameObjectMgr::AddNewGameObject(*boundary);
	}

	//// Add RIGHT column (excluding top and bottom elements)
	for (int i = 0; i < GRID_ROW + 1; i++)
	{
		Boundary* boundary = new Boundary(gridComponent.GetGridPos(GRID_COL + 1, i));
		boundary->SetDirection(E_DIR_BOUNDARY::RIGHT);
		//set corner
		if (i == 0)
			boundary->SetCorner();
		GameObjectMgr::AddNewGameObject(*boundary);
	}

	//// Add BTM row
	for (int j = GRID_COL + 1; j > 0; j--)
	{
		Boundary* boundary = new Boundary(gridComponent.GetGridPos(j, GRID_ROW + 1));
		boundary->SetDirection(E_DIR_BOUNDARY::DOWN);
		//set corner
		if (j == GRID_COL + 1)
			boundary->SetCorner();
		GameObjectMgr::AddNewGameObject(*boundary);
	}

	//// Add LEFT column (excluding top and bottom elements)
	for (int i = GRID_ROW + 1 ; i > 0; i--)
	{
		Boundary* boundary = new Boundary(gridComponent.GetGridPos(0, i));
		boundary->SetDirection(E_DIR_BOUNDARY::LEFT);
		//set corner
		if (i == GRID_ROW + 1)
			boundary->SetCorner();
		GameObjectMgr::AddNewGameObject(*boundary);
	}
	
	///*create game object by level file info
	for (int i = 0; i < level.size(); i++)
	{
		for (int j = 0; j < level[i].size(); j++)
		{
			GameAreaObject* item = level[i][j];
			if (item)
			{
				//add level
				switch (item->m_type)
				{
				case E_OBJTYPE::E_TILE:
				{
					Play::Point2D pos{ item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					Tile* tile = new Tile(gridComponent.GetGridPos(i + 1, j), E_TILE_COLOR::BLUE);
					GameObjectMgr::AddNewGameObject(*tile);
				}
				break;
				case E_OBJTYPE::E_MOUSE:
				{
					Play::Point2D pos{ item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					Mouse* mice = nullptr;

					if (item->m_color == 0)
						mice = new Mouse(gridComponent.GetGridPos(i + 1 , j ), E_MOUSE_COLOR::GREY);
					if (item->m_color == 1)
						mice = new Mouse(gridComponent.GetGridPos(i + 1, j ), E_MOUSE_COLOR::DARK_GREY);
					if (item->m_color == 2)
						mice = new Mouse(gridComponent.GetGridPos(i + 1, j ), E_MOUSE_COLOR::WHITE);
					if (mice)
					{
						mice->SetInitRotation(static_cast<float>(item->rot * 90));
						GameObjectMgr::AddNewGameObject(*mice);
					}
				}
				break;
				case E_OBJTYPE::E_MOUSETRAP:
				{
					Play::Point2D pos{ item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					MouseTrap* trap = new MouseTrap(gridComponent.GetGridPos(i + 1, j ));
					trap->m_rot = static_cast<float>(item->rot * 90);
					if (item->trap_color)
						trap->SetColor(E_TRAPCOLOR::DARK_WOOD);
					else
						trap->SetColor(E_TRAPCOLOR::LIGHT_WOOD);
					GameObjectMgr::AddNewGameObject(*trap);
				}
				break;
				case E_OBJTYPE::E_CHEESE:
				{
					Play::Point2D pos{ item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					Cheese* cz = new Cheese(gridComponent.GetGridPos(i + 1, j ));

					GameObjectMgr::AddNewGameObject(*cz);
				}
				break;
				default:
					break;
				}
			}


		}
	}
}

//when load level add a boundary outside
void Level::LoadLevel()
{
	GameAreaInfo& gameAreaInfo = ResoureMgr::LoadLevel(levelName);
	std::vector<std::vector<GameAreaObject*>>& level = gameAreaInfo.objects;


	//*Create Mouse Hole*//
	Play::Point2D pos1{ gameAreaInfo.EntryPos.x * GRID_SIZE + GRID_SIZE / 2 - GRID_SIZE, gameAreaInfo.EntryPos.y * GRID_SIZE + GRID_SIZE / 2 };
	MouseHole* mouse_entry = nullptr;
	if (gameAreaInfo.EntryPos.x == 0)
	{
		mouse_entry = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.EntryPos.x, gameAreaInfo.EntryPos.y),E_MOUSEHOLE_DIR::LEFT);
	}
	else if (gameAreaInfo.EntryPos.x == (GRID_COL  + 1))
	{
		mouse_entry = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.EntryPos.x, gameAreaInfo.EntryPos.y), E_MOUSEHOLE_DIR::RIGHT);
	}
	else if (gameAreaInfo.EntryPos.y == 0)
	{
		mouse_entry = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.EntryPos.x, gameAreaInfo.EntryPos.y), E_MOUSEHOLE_DIR::TOP);
	}
	else if (gameAreaInfo.EntryPos.y == GRID_ROW + 1)
	{
		mouse_entry = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.EntryPos.x, gameAreaInfo.EntryPos.y), E_MOUSEHOLE_DIR::BOTTOM);
	}
	if(mouse_entry)
	GameObjectMgr::AddNewGameObject(*mouse_entry);

	Play::Point2D pos2{ gameAreaInfo.ExitPos.x * GRID_SIZE + GRID_SIZE / 2 - GRID_SIZE, gameAreaInfo.ExitPos.y * GRID_SIZE + GRID_SIZE / 2 };
	MouseHole* mouse_Exit = nullptr;
	if (gameAreaInfo.ExitPos.x == -1)
	{
		mouse_Exit = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.ExitPos.x, gameAreaInfo.ExitPos.y), E_MOUSEHOLE_DIR::LEFT);
	}
	else if (gameAreaInfo.ExitPos.x == (GRID_COL + 1))
	{
		mouse_Exit = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.ExitPos.x, gameAreaInfo.ExitPos.y), E_MOUSEHOLE_DIR::RIGHT);
	}
	else if (gameAreaInfo.ExitPos.y == 0)
	{
		mouse_Exit = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.ExitPos.x, gameAreaInfo.ExitPos.y), E_MOUSEHOLE_DIR::TOP);
	}
	else if (gameAreaInfo.ExitPos.y == GRID_ROW + 1)
	{
		mouse_Exit = new MouseHole(gridComponent.GetGridPos(gameAreaInfo.ExitPos.x, gameAreaInfo.ExitPos.y), E_MOUSEHOLE_DIR::BOTTOM);
	}
	if (mouse_Exit)
	{
		mouse_Exit->SetType(E_MOUSEHOLE_TYPE::EXIT);
	}
	GameObjectMgr::AddNewGameObject(*mouse_Exit);

	///*create boundary outside game area*//
	int Boundary_row = GRID_COL + 1;
	int Boundary_col = GRID_ROW + 2;
	//add left column
	for (int j = 1; j < Boundary_col; j++)
	{
		Play::Point2D pos{ 0 * GRID_SIZE + GRID_SIZE / 2 - GRID_SIZE, j * GRID_SIZE + GRID_SIZE / 2 };
		Boundary* boundary = new Boundary(GameToWorld(pos));
		boundary->SetDirection(E_DIR_BOUNDARY::LEFT);
		//set corner
		if (j == Boundary_col - 1)
			boundary->SetCorner();
		GameObjectMgr::AddNewGameObject(*boundary);
	}

	// Add btm column (excluding top and bottom elements)
	for (int i = 0; i < Boundary_row ; i++)
	{

		Play::Point2D pos{ i * GRID_SIZE + GRID_SIZE / 2, (Boundary_col - 1) * GRID_SIZE + GRID_SIZE / 2 };
		Boundary* boundary = new Boundary(GameToWorld(pos));
		boundary->SetDirection(E_DIR_BOUNDARY::DOWN);
		//set corner
		if (i == Boundary_row - 1)
			boundary->SetCorner();
		GameObjectMgr::AddNewGameObject(*boundary);
	}

	// Add right row
	for (int j = Boundary_col - 2; j >= 0; j--)
	{

		Play::Point2D pos{ (Boundary_row - 1)  * GRID_SIZE + GRID_SIZE / 2, j * GRID_SIZE + GRID_SIZE / 2 };
		Boundary* boundary = new Boundary(GameToWorld(pos));
		boundary->SetDirection(E_DIR_BOUNDARY::RIGHT);
		//set corner
		if (j == 0)
			boundary->SetCorner();
		GameObjectMgr::AddNewGameObject(*boundary);
	}

	// Add top column (excluding top and bottom elements)
	for (int i = Boundary_row - 2; i >  -2; i--)
	{
		Play::Point2D pos{ i * GRID_SIZE + GRID_SIZE / 2, 0 * GRID_SIZE + GRID_SIZE / 2 };
		Boundary* boundary = new Boundary(GameToWorld(pos));
		//set corner
		if (i == -1)
			boundary->SetCorner();
		GameObjectMgr::AddNewGameObject(*boundary);
	}

	///*create game object by level file info
	for (int i = 0; i < level.size(); i++)
	{
		for (int j = 0; j < level[i].size(); j++)
		{
            GameAreaObject* item = level[i][j];
            if (item)
            {
				//add level
				switch (item->m_type)
				{
				case E_OBJTYPE::E_TILE:
				{
					Play::Point2D pos{ item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					Tile* tile = new Tile(GameToWorld(pos),E_TILE_COLOR::BLUE);
					GameObjectMgr::AddNewGameObject(*tile);
				}
				break;
				case E_OBJTYPE::E_MOUSE:
				{
					Play::Point2D pos{ item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					Mouse* mice = nullptr;

					if(item->m_color == 0)
						mice = new Mouse(GameToWorld(pos),E_MOUSE_COLOR::GREY);
					if (item->m_color == 1)
						mice = new Mouse(GameToWorld(pos), E_MOUSE_COLOR::DARK_GREY);
					if (item->m_color == 2)
						mice = new Mouse(GameToWorld(pos), E_MOUSE_COLOR::WHITE);
					if (mice)
					{
						mice->SetInitRotation(static_cast<float>(item->rot * 90));
						GameObjectMgr::AddNewGameObject(*mice);
					}
				}
				break;
				case E_OBJTYPE::E_MOUSETRAP:
				{
					Play::Point2D pos{ item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					MouseTrap* trap = new MouseTrap(GameToWorld(pos));
					trap->m_rot = static_cast<float>(item->rot * 90);
					if (item->trap_color)
						trap->SetColor(E_TRAPCOLOR::DARK_WOOD);
					else
						trap->SetColor(E_TRAPCOLOR::LIGHT_WOOD);
					GameObjectMgr::AddNewGameObject(*trap);
				}
				break;
				case E_OBJTYPE::E_CHEESE:
				{
					Play::Point2D pos{ item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					Cheese* cz = new Cheese(GameToWorld(pos));

					GameObjectMgr::AddNewGameObject(*cz);
				}
				break;
				default:
					break;
				}
			}

		
		}
	}
}
