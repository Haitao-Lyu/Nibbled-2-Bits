#pragma once
#include "GameFlowState.h"
#include "../UI/Panel.h"
class MainMenuState :public GameFlowState
{
	//Load MainMenu Panel
	Panel* MainMenuPanel = nullptr;

	bool isShowInputBox = false;
public:

	MainMenuState();

	virtual ~MainMenuState() override;

	void OnEnter() override;

	void OnExit() override;

	GameFlowState* OnUpdate() override;

};