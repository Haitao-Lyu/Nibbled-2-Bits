#include "Level.h"
#include "../GameObject/GameObjectMgr.h"
Level::Level()
{
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
