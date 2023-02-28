#define PLAY_IMPLEMENTATION
#include "pch.h"

#include "MainGame.h"
#include "Level/Level.h"
#include "GameTool/Timer.h"
#include "Manager/ResourceMgr.h"
#include "Manager/GameObjectMgr.h"
#include "GameObject/Component/CollisionSystem.h"
#include "UI/Panel.h"
#include "UI/Button.h"
#include "GameObject/Tube.h"

Panel panel({ (DISPLAY_WIDTH - GAME_AREA_WIDTH)/2 - 10,DISPLAY_HEIGHT/2 }, static_cast<short>(814/1.5) , static_cast<short>(497/1.5) , "Panel_not_tab");

Level level1("CHEESE");

Button btn({ 100,100 }, 100, 100, "iron_tube_cross");
Button btn2({ 100,100 }, 100, 100, "iron_tube_two_way");

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	Play::CentreAllSpriteOrigins();
	//level1.LoadLevel();
	level1.LoadLevelBaseOnGrid(); //something wrong in gameobject map
	panel.gridComponent.AddToGrids(&btn);
	panel.gridComponent.AddToGrids(&btn2);

}

bool MainGameUpdate( float elapsedTime )
{
	Timer::UpdateDeltaTime(elapsedTime);
	ResoureMgr::DrawBackground(E_BKCOLOR::YELLOW);

	panel.Update();
	level1.Update();

	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_TILE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSETRAP);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_CHEESE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_BOUNDARY);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSEHOLE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_TUBE);
	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

