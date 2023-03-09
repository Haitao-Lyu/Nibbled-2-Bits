#include "pch.h"
#include "MainGameState.h"
#include "MainMenuState.h"
#include "../Manager/LevelMgr.h"
#include "../Manager/GameObjectMgr.h"
#include "../Manager/ResourceMgr.h"
#include "../UI/EventCenter.h"
#include "../Particle/ParticleManager.h"

static int levelBackGroundColor = -1;

MainGameState::MainGameState()
{

}


MainGameState::~MainGameState()
{
	 
}

void MainGameState::OnEnter()
{
	levelBackGroundColor = Play::RandomRollRange(0, 5);
	LevelMgr* instance = LevelMgr::GetInstance();

	//init All Level
	//will add two level every thing time enter
	instance->AddNewLevel("Level1");
	instance->AddNewLevel("Level2");
	instance->AddNewLevel("Level3");
	instance->AddNewLevel("Level4");

	//something wrong in game object map
	EventListener exitListener("ExitGameListener");
	exitListener.addEvent([this]()
		{
			this->isBackToMainMenu = true;
		});
	EventCenter::RegisterListener("ExitButtonPressed", exitListener);
}

GameFlowState* MainGameState::OnUpdate()
{
	//draw background
	ResoureMgr::DrawBackground(E_BKCOLOR::GREEN);
	//update Level Particle
	ParticleMgr::GetInstance().UpdateEmitterList();
	//define render order
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_COFFEESPILL);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_STICKYSPILL);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_TILE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSETRAP);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_CHEESE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_BOUNDARY);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_MOUSEHOLE);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_TUBE);

	//Update Level Logic
	LevelMgr::GetInstance()->Update();

	if (isBackToMainMenu)
	{
		return new MainMenuState();
	}

	return nullptr;

}

void MainGameState::OnExit()
{
	EventCenter::UnregisterListenersByEvent("ExitButtonPressed");
	LevelMgr::GetInstance()->Clear();
}
