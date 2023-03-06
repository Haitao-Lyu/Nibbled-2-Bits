#include "pch.h"
#include "LevelState.h"
#include "MainMenuState.h"
#include "../Manager/LevelMgr.h"
#include "../Manager/GameObjectMgr.h"
#include "../UI/EventCenter.h"
GameFlowState* LevelState::OnUpdate()
{
	//define render order
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_TILE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSETRAP);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_CHEESE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_BOUNDARY);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSEHOLE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_TUBE);

	if (currentLevel)
	{
		//Only Contain UI Panel information now, Game object info are in Game object manager
		currentLevel->Update();
	}

	if (Play::KeyPressed(VK_ESCAPE))
	{
		return new MainMenuState();
	}
	return nullptr;

}

LevelState::LevelState()
{

}


LevelState::~LevelState()
{
	
}

void LevelState::OnEnter()
{
	LevelMgr* instance = LevelMgr::GetInstance();

	//init All Level
	instance->AddNewLevel("Level1");
	instance->AddNewLevel("Level2");

	//Set Current Level
	Level* lev1 = instance->GetLevel(0);
	if (!lev1)
		return;

	lev1->LoadLevelPanel();
	lev1->LoadLeveltoScene(); //something wrong in game object map

	currentLevel = lev1;
	//restart
	EventListener restartListener("MouseRestartGameListener");
	restartListener.addEvent([lev1]()
		{
			lev1->Clear();
			lev1->LoadLeveltoScene();
		});
	EventCenter::RegisterListener("GameRestart", restartListener);
}

void LevelState::OnExit()
{
	EventCenter::UnregisterListenersByEvent("GameRestart");
}
