#include "pch.h"
#include "MainMenuState.h"

GameFlowState* MainMenuState::OnUpdate()
{
	if (Play::KeyPressed(VK_SPACE))
	{
		return new MainMenuState();
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
