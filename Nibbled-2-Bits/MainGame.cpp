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
#include "UI/EventCenter.h"
#include "GameObject/Tube.h"


Level level1("TUBETEST");


void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	Play::CentreAllSpriteOrigins();


	//level1.LoadLevel();
	level1.LoadLevelBaseOnGrid(); //something wrong in gameobject map
	level1.LoadLevelPanel();

	//restart
	EventListener* restartListener = new EventListener("MouseRestartGameListener");
	restartListener->addEvent([]() 
		{ 
			GameObjectMgr::ClearAllGameobjects(); 
			level1.LoadLevelBaseOnGrid(); 
		});
	EventCenter::RegisterListener("GameRestart", *restartListener);
}

bool MainGameUpdate( float elapsedTime )
{
	Timer::UpdateDeltaTime(elapsedTime);
	ResoureMgr::DrawBackground(E_BKCOLOR::WOOD);

	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_TILE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSETRAP);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_CHEESE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_BOUNDARY);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSEHOLE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_TUBE);

	level1.Update();

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

