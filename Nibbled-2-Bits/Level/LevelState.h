#pragma once
#include "GameFlowState.h"
#include "Level.h"
class LevelState:public GameFlowState
{

	Level* currentLevel = nullptr;

public:
	LevelState();

	virtual ~LevelState() override;

	void OnEnter() override;

	void OnExit() override;

	GameFlowState* OnUpdate() override;

};

