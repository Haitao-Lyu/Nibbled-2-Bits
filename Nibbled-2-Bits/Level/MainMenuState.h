#pragma once
#include "GameFlowState.h"
class MainMenuState :public GameFlowState
{
public:

	MainMenuState();

	virtual ~MainMenuState() override;

	void OnEnter() override;

	void OnExit() override;

	GameFlowState* OnUpdate() override;

};