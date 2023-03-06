#include "pch.h"
#include "MainMenuState.h"
#include "LevelState.h"
GameFlowState* MainMenuState::OnUpdate()
{
	if (Play::KeyPressed(VK_SPACE))
	{
		return new LevelState();
	}
	return nullptr;
}

MainMenuState::MainMenuState()
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::OnEnter()
{
	
}

void MainMenuState::OnExit()
{
	
}
