#include "pch.h"
#include "ApplicationMgr.h"
#include "../Level/MainMenuState.h"
ApplicationMgr::ApplicationMgr()
{
	m_gameState = new MainMenuState();
}

ApplicationMgr::~ApplicationMgr()
{

}

void ApplicationMgr::Update()
{
	GameFlowState* newState = m_gameState->OnUpdate();
	if (newState != nullptr)
	{
		m_gameState->OnExit();
		delete m_gameState;
		m_gameState = newState;
		m_gameState->OnEnter();
	}
}
