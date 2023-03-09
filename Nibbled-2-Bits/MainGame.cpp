#define PLAY_IMPLEMENTATION
#include "pch.h"

#include "MainGame.h"
#include "Level/Level.h"
#include "GameTool/Timer.h"
#include "Manager/ResourceMgr.h"
#include "Manager/GameObjectMgr.h"
#include "Manager/ApplicationMgr.h"
#include "Manager/LevelMgr.h"
#include "GameObject/Component/CollisionSystem.h"
#include "UI/Panel.h"
#include "UI/Button.h"
#include "UI/EventCenter.h"
#include "GameObject/Tube.h"

//TODO: Fix Coordination system OR Blender Mode

//TODO: Feature in Order
// coffee acceleration
// Cat enemy
// weather effect
// shadow phantom mouse + effect

// Enter Level Instruction Panel

// Lose Game Panel

// Refactor code structure 


void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	Play::CentreAllSpriteOrigins();
}

bool MainGameUpdate( float elapsedTime )
{
	Timer::UpdateDeltaTime(elapsedTime);

	ApplicationMgr::Update();

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

