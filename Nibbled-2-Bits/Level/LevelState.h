#pragma once
#include "GameFlowState.h"

class LevelState:public GameFlowState
{


public:
	LevelState();

	virtual ~LevelState() override;

	void OnEnter() override;

	void OnExit() override;

	GameFlowState* OnUpdate() override;

};

