#include "pch.h"
#include "Level.h"
#include "../GameObject/GameObjectMgr.h"
#include "../GameObject/Tile.h"
#include "../GameObject/Mouse.h"
#include "../GameObject/Boundary.h"
#include "../ResourceMgr.h"
#include "../MainGame.h"
static const int GAME_AREA_WIDTH{ 870 };
static const int GAME_AREA_HEIGHT{ 720 };
static const int GRID_SIZE{ 50 };
static const int BOARDER_PIXELS{ 35 };
static const int GRID_ROW = 16;
static const int GRID_COL = 13;
Level::Level()
{
    m_mapinfo.resize(GRID_ROW);
	for (std::vector<int>& row : m_mapinfo)
	{
		row.resize(GRID_COL);
	}
   
}

Level::~Level()
{

}

void Level::render()
{
	
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
//from mouse editor
Play::Point2D GameToWorld(Play::Point2D pos) {
	Play::Point2D botLeftGrid{ DISPLAY_WIDTH - GAME_AREA_WIDTH + 25, DISPLAY_HEIGHT - GAME_AREA_HEIGHT };
	return pos + botLeftGrid;
}
//when load level add a boundary outside
void Level::InitializeByName(std::string levelName)
{
	std::vector<std::vector<GameAreaObject*>>& level = ResoureMgr::LoadLevel(levelName);

	int Boundary_row = GRID_ROW + 1;
	int Boundary_col = GRID_COL + 2;
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
					Tile* tile = new Tile(GameToWorld(pos),E_TILE_COLOR::GREEN);
					GameObjectMgr::AddNewGameObject(*tile);
				}
				break;
				case E_OBJTYPE::E_MOUSE:
				{
					Play::Point2D pos{ item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					Mouse* mice = new Mouse(GameToWorld(pos));
					GameObjectMgr::AddNewGameObject(*mice);
				}
				break;
				default:
					break;
				}
			}

		
		}
	}
}
