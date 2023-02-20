#define PLAY_IMPLEMENTATION
#include "pch.h"

#include "MainGame.h"
#include "GameTool/Timer.h"
#include "ResourceMgr.h"
#include "GameObject/Mouse.h"
#include "GameObject/Tile.h"
#include "Level/Level.h"
#include "GameObject/GameObjectMgr.h"
//#include "GameObject/Mouse.h"

//Mouse mice_darkgrey{100 ,100};
//Mouse mice_white{ 200 ,200 ,E_MOUSE_COLOR::WHITE};
//Mouse mice_grey{ 300 ,300 ,E_MOUSE_COLOR::GREY };
Level level1;
// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	Play::CentreAllSpriteOrigins();
	level1.InitializeByName("TILES");
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Timer::UpdateDeltaTime(elapsedTime);
	ResoureMgr::DrawBackground(E_BKCOLOR::WOOD);

	//static int frame = 0;
	//if (Play::KeyPressed(VK_SPACE))
	//{
	//	mice_darkgrey.SetMouseState((E_MOUSE_STATE)frame);
	//	mice_white.SetMouseState((E_MOUSE_STATE)frame);
	//	mice_grey.SetMouseState((E_MOUSE_STATE)frame);
	//	frame++;
	//}
	//mice_darkgrey.Update();
	//mice_white.Update();
	//mice_grey.Update();

	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_TILE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSE);

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

