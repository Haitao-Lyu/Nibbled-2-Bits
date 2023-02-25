#pragma once
class BaseState
{
private:

public:
	BaseState();
	~BaseState();
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
};
