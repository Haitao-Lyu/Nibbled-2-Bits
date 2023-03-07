#pragma once
#include "GameFlowState.h"
#include "Level.h"
class MainGameState:public GameFlowState
{
private:
	bool isBackToMainMenu = false;
public:
	MainGameState();

	virtual ~MainGameState() override;

	void OnEnter() override;

	void OnExit() override;

	GameFlowState* OnUpdate() override;

};

