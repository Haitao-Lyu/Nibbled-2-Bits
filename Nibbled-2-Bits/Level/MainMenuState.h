#pragma once
#include "GameFlowState.h"
class MainMenuState :public GameFlowState
{
	//Load MainMenu Panel

public:

	MainMenuState();

	virtual ~MainMenuState() override;

	void OnEnter() override;

	void OnExit() override;

	GameFlowState* OnUpdate() override;

};