#include "pch.h"
#include "LevelState.h"
#include "MainMenuState.h"

GameFlowState* LevelState::OnUpdate()
{
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
	
}

void LevelState::OnExit()
{
	
}
