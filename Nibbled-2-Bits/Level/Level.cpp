#include "pch.h"
#include "Level.h"
#include "../Manager/ResourceMgr.h"
#include "../Manager/GameObjectMgr.h"
#include "../MainGame.h"
#include "../UI/Button.h"
#include "../GameObject/Tile.h"
#include "../GameObject/Mouse.h"
#include "../GameObject/Boundary.h"
#include "../GameObject/MouseTrap.h"
#include "../GameObject/Cheese.h"
#include "../GameObject/MouseHole.h"
#include "../GameObject/Tube.h"
#include "../UI/EventCenter.h"


static const char* tube_cross_name = "iron_tube_cross";
static const char* tube_one_name = "iron_tube_one_way";
static const char* tube_three_name = "iron_tube_three_way";
static const char* tube_two_name = "iron_tube_two_way";

//from mouse editor
Play::Point2D GameToWorld(Play::Point2D pos) {
	Play::Point2D botLeftGrid{ DISPLAY_WIDTH - GAME_AREA_WIDTH + 25, DISPLAY_HEIGHT - GAME_AREA_HEIGHT };
	return pos + botLeftGrid;
}

Level::Level(const char* name)
{
	m_mapinfo.resize(GRID_COL + 2);
	for (std::vector<int>& row : m_mapinfo)
	{
		row.resize(GRID_ROW + 2,-1);
	}
	levelName = name;
	//Load game area level info
	m_gamePanel = new Panel({ GAME_AREA_WIDTH, DISPLAY_HEIGHT / 2 }, DISPLAY_HEIGHT, GAME_AREA_WIDTH);
	m_gamePanel->gridComponent.InitGridInfo(GRID_ROW + 2, GRID_COL + 2, GAME_AREA_HEIGHT + 1, GAME_AREA_WIDTH - 50, { GAME_AREA_WIDTH, DISPLAY_HEIGHT / 2 });
}

Level::~Level()
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

void Level::Update()
{
	if (m_gamePanel)
	{
		m_gamePanel->isVisable = false;
		m_gamePanel->Update();
	}


	if(m_itemPanel)
		m_itemPanel->Update();

	CheckPanelEvent();

	LevelControl();
}

void Level::FromItemPanelAddToLevel(GridItem& grid, short x, short y)
{
	//if item exist remove item
	if (m_mapinfo[x][y] != -1)
	{
		m_itemPanel->gridComponent.heldGridItem = nullptr;
		return;
	}
	else
	{
		Tube* obj = new Tube(grid.GetPos(), m_itemPanel->gridComponent.heldGridItem->m_info.tube_type);
		//if not, create obj,  put UI item into game panel grid list
		Button* btn = nullptr;
		if (std::strcmp(obj->spriteName, tube_cross_name) == 0)
		{
			btn = new Button({ 100,100 }, 50, 50, "iron_tube_cross");
		}
		if (std::strcmp(obj->spriteName, tube_one_name) == 0)
		{
			btn = new Button({ 100,100 }, 50, 50, "iron_tube_one_way");
		}
		if (std::strcmp(obj->spriteName, tube_two_name) == 0)
		{
			btn = new Button({ 100,100 }, 50, 50, "iron_tube_two_way");
		}
		if (std::strcmp(obj->spriteName, tube_three_name) == 0)
		{
			btn = new Button({ 100,100 }, 50, 50, "iron_tube_three_way");
		}
		m_gamePanel->gridComponent.AddToGrids(btn, x, y);
		//add level map info
		m_mapinfo[x][y] = obj->GetID();
		//add info to grid
	}
	m_itemPanel->gridComponent.heldGridItem = nullptr;
}

void Level::FromLevelMoveToLevel(GridItem &grid, short x, short y)
{
	//if item exist remove item
	if (m_mapinfo[x][y] != -1)
	{
		m_gamePanel->gridComponent.heldGridItem = nullptr;
		return;
	}
	else
	{
		// move old game object
		GameObjectMgr::GetGameObjectByid(m_mapinfo[grid.m_info.m_x][grid.m_info.m_y])->SetPosition(m_gamePanel->gridComponent.GetGridPos(x,y));
		//add old game obj id to level map info
		m_mapinfo[x][y] = m_mapinfo[grid.m_info.m_x][grid.m_info.m_y];
		//remove old pos level info
		m_mapinfo[grid.m_info.m_x][grid.m_info.m_y] = -1;

		//move old button
		m_gamePanel->gridComponent.AddToGrids(grid.GetGridUIElement(), x, y);
		//clear old grid button
		grid.Clear();
	}
	m_gamePanel->gridComponent.heldGridItem = nullptr;
}

void Level::LevelControl()
{
	//right click in game panel rotate obj
	for (std::vector<GridItem>& grids : m_gamePanel->gridComponent.gridList)
	{
		for (GridItem& grid : grids)
		{
			if (grid.GetGridUIElement())
			{
				if (grid.GetGridUIElement()->OnClickRight())
				{
					//if grid item is clicked, both button and game object rotate
					grid.GetGridUIElement()->m_rot += 90;
					GameObjectMgr::GetGameObjectByid(m_mapinfo[grid.m_info.m_x][grid.m_info.m_y])->Rotate(+90);
				}
			}
		}
	}
}

void Level::CheckPanelEvent()
{
	//if holding item from item panel
	for (std::vector<GridItem>& grids : m_itemPanel->gridComponent.gridList)
	{
		for (GridItem& grid : grids)
		{
			//if has ui element - enable drag
			if (grid.GetGridUIElement())
			{
				if (grid.GetGridUIElement()->OnHolding())
				{
					//create a temp btn image follow mouse based on grid
					UIElement btn;
					btn.SetSpriteName(grid.GetGridUIElement()->m_spriteName);
					btn.SetPosition(Play::GetMousePos());
					btn.Render();
					//get held grid item info
					m_itemPanel->gridComponent.heldGridItem = &grid;
				}
				else
				{
					if (m_itemPanel->gridComponent.heldGridItem)
					{
						//EventCenter::PostEvent("MouseRelease");
						//check if hover in game panel grid
						for (std::vector<GridItem>& grids_2 : m_gamePanel->gridComponent.gridList)
						{
							for (GridItem& grid_new : grids_2)
							{
								if (grid_new.OnHover())
								{
									if (!Play::KeyDown(VK_LBUTTON))
									{
										//add to level map info, add to level panel
										FromItemPanelAddToLevel(grid_new, grid_new.m_info.m_x, grid_new.m_info.m_y);
									}
								}
							
							}
						}
					}
				}
			}
		}
	}

	//if holding item from level
	for (std::vector<GridItem>& grids : m_gamePanel->gridComponent.gridList)
	{
		for (GridItem& grid_hold : grids)
		{
			//if has ui element, grab and create new one follow the mouse
			if (grid_hold.GetGridUIElement())
			{
				if (grid_hold.GetGridUIElement()->OnHolding())
				{
					//create a temp btn image follow mouse based on grid
					UIElement btn(*grid_hold.GetGridUIElement());
					btn.m_rot = grid_hold.GetGridUIElement()->m_rot;
					btn.SetSpriteName(grid_hold.GetGridUIElement()->m_spriteName);
					btn.SetPosition(Play::GetMousePos());
					btn.Render();
					//get held grid item info
					m_gamePanel->gridComponent.heldGridItem = &grid_hold;
				}
				else
				{
					//OnRelease Key create object
					if (m_gamePanel->gridComponent.heldGridItem)
					{
						if (!Play::KeyDown(VK_LBUTTON))
						{
							if (!m_gamePanel->OnHover())
							{
								//if drag out of game panel, delete it
								GameObjectMgr::RemoveGameObjectByid(m_mapinfo[m_gamePanel->gridComponent.heldGridItem->m_info.m_x][m_gamePanel->gridComponent.heldGridItem->m_info.m_y]);
								//map info remove
								m_mapinfo[m_gamePanel->gridComponent.heldGridItem->m_info.m_x][m_gamePanel->gridComponent.heldGridItem->m_info.m_y] = -1;
								//remove from panel item
								m_gamePanel->gridComponent.RemoveGridItemByID(m_gamePanel->gridComponent.heldGridItem->GetID());
							}
						}
						//release mouse key event
						//EventCenter::PostEvent("MouseRelease");
						for (std::vector<GridItem>& grids_2 : m_gamePanel->gridComponent.gridList)
						{
							for (GridItem& grid_new : grids_2)
							{
								if (grid_new.OnHover())
								{
									if (!Play::KeyDown(VK_LBUTTON))
									{
										//add to level map info, add to level panel,pass in graded grid
										FromLevelMoveToLevel(*m_gamePanel->gridComponent.heldGridItem, grid_new.m_info.m_x, grid_new.m_info.m_y);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Level::LoadLevelPanel()
{
	//All elements in a panel should scale by the scale of panel
	Panel* panel = new Panel({ (DISPLAY_WIDTH - GAME_AREA_WIDTH) / 2 + 25,DISPLAY_HEIGHT / 2 }, DISPLAY_HEIGHT, (DISPLAY_WIDTH - GAME_AREA_WIDTH) + 50, "");
	panel->gridComponent.InitGridInfo(2, 3, panel->m_height - 300, panel->m_width, {panel->m_pos.x, panel->m_pos.y});

	m_itemPanel = panel;

	Button* btn2 = new Button({ 100,100 }, 100, 100, "iron_tube_two_way");
	Button* btn3 = new Button({ 100,100 }, 100, 100, "iron_tube_three_way");
	Button* btn4 = new Button({ 100,100 }, 100, 100, "iron_tube_one_way");

	m_itemPanel->gridComponent.Push_back_Grids(btn2);
	m_itemPanel->gridComponent.Push_back_Grids(btn3);
	m_itemPanel->gridComponent.Push_back_Grids(btn4);
}

void Level::LoadLevelBaseOnGrid()
{
	GameAreaInfo& gameAreaInfo = ResoureMgr::LoadLevel(levelName);
	// col:16  row: 13
	std::vector<std::vector<GameAreaObject*>>& level = gameAreaInfo.objects;
	GridComponent& gridComponent = m_gamePanel->gridComponent;
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
	{
		GameObjectMgr::AddNewGameObject(*mouse_entry);
		//Update id map
		m_mapinfo[gameAreaInfo.EntryPos.x][gameAreaInfo.EntryPos.y] = mouse_entry->GetID();
	}


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
	if (mouse_Exit)
	{
		GameObjectMgr::AddNewGameObject(*mouse_Exit);
		//Update id map
		m_mapinfo[gameAreaInfo.ExitPos.x][gameAreaInfo.ExitPos.y] = mouse_Exit->GetID();
	}


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
		//Update id map
		m_mapinfo[j][0] = boundary->GetID();
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
		//Update id map
		m_mapinfo[GRID_COL + 1][i] = boundary->GetID();
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
		//Update id map
		m_mapinfo[j][GRID_ROW + 1] = boundary->GetID();
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
		//Update id map
		m_mapinfo[0][i] = boundary->GetID();
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

					Tile* tile = new Tile(gridComponent.GetGridPos(i + 1, j), E_TILE_COLOR::BLUE);
					GameObjectMgr::AddNewGameObject(*tile);
					//Update id map
					m_mapinfo[i + 1][j] = tile->GetID();
				}
				break;
				case E_OBJTYPE::E_MOUSE:
				{

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
					//Update id map
					m_mapinfo[i + 1][j] = mice->GetID();
				}
				break;
				case E_OBJTYPE::E_MOUSETRAP:
				{

					MouseTrap* trap = new MouseTrap(gridComponent.GetGridPos(i + 1, j ));
					trap->m_rot = static_cast<float>(item->rot * 90);
					if (item->trap_color)
						trap->SetColor(E_TRAPCOLOR::DARK_WOOD);
					else
						trap->SetColor(E_TRAPCOLOR::LIGHT_WOOD);
					GameObjectMgr::AddNewGameObject(*trap);
					m_mapinfo[i + 1][j] = trap->GetID();
				}
				break;
				case E_OBJTYPE::E_CHEESE:
				{

					Cheese* cz = new Cheese(gridComponent.GetGridPos(i + 1, j ));

					GameObjectMgr::AddNewGameObject(*cz);
					//Update id map
					m_mapinfo[i + 1][j] = cz->GetID();
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
void Level::LoadLevel_Old()
{
	GameAreaInfo& gameAreaInfo = ResoureMgr::LoadLevel(levelName);
	std::vector<std::vector<GameAreaObject*>>& level = gameAreaInfo.objects;

	GridComponent& gridComponent = m_gamePanel->gridComponent;
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
