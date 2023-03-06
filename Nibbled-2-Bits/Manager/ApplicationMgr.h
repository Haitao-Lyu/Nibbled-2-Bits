#pragma once
#include "../Level/GameFlowState.h"

class ApplicationMgr
{

private:
	GameFlowState* m_gameState;
public:
	ApplicationMgr();
	~ApplicationMgr();

	void Update();

};

