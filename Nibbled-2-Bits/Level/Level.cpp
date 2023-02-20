#include "pch.h"
#include "Level.h"
#include "../GameObject/GameObjectMgr.h"
#include "../GameObject/Tile.h"
#include "../GameObject/Mouse.h"
#include "../ResourceMgr.h"
#include "../MainGame.h"
int GAME_AREA_WIDTH{ 870 };
int GAME_AREA_HEIGHT{ 720 };
int GRID_SIZE{ 50 };
int BOARDER_PIXELS{ 35 };

Level::Level()
{
    m_mapinfo.resize(16);
	for (std::vector<int>& row : m_mapinfo)
	{
		row.resize(13);
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


void Level::InitializeByName(std::string levelName)
{
	std::vector<std::vector<GameAreaObject*>>& level = ResoureMgr::LoadLevel(levelName);

	for (std::vector<GameAreaObject*>& row : level)
	{
		for (GameAreaObject* item : row)
		{
			if (item)
				switch (item->m_type)
				{
				case E_OBJTYPE::E_TILE:
				{
                    Play::Point2D pos { item->posx * GRID_SIZE + GRID_SIZE / 2, item->posy * GRID_SIZE + GRID_SIZE / 2 };
					Tile* tile = new Tile(GameToWorld(pos));
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
