#pragma once
class StateInterface
{
public:
	StateInterface() = default;
	virtual ~StateInterface() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual StateInterface* OnUpdate() = 0;
};

