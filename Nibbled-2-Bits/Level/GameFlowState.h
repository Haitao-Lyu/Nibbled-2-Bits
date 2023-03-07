#pragma once
class GameFlowState
{
public:
	GameFlowState() = default;
	virtual ~GameFlowState() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual GameFlowState* OnUpdate() = 0;
};