#include "Mouse.h"
#include "../GameTool/DebugTool.h"

Mouse::Mouse(Play::Point2D pos, E_MOUSE_COLOR COLOR) :GameObject(pos,E_OBJTYPE::E_MOUSE)
{
	switch (COLOR)
	{
	case E_MOUSE_COLOR::DARK_GREY:
		m_Color = c_darkGrey;
		break;
	case E_MOUSE_COLOR::GREY:
		m_Color = c_grey;
		break;
	case E_MOUSE_COLOR::WHITE:
		m_Color = c_white;
		break;
	}
	runState = new MouseRunState(*this);
	dieState = new MouseDieState(*this);
	idleState = new MouseIdleState(*this);
	jumpState = new MouseJumpState(*this);
	walkState = new MouseWalkState(*this);
	hurtState = new MouseHurtState(*this);
	whackedState = new MouseWhackedState(*this);
	m_state = idleState;
}

Mouse::Mouse(float x, float y, E_MOUSE_COLOR COLOR) :GameObject(x, y, E_OBJTYPE::E_MOUSE)
{
	switch (COLOR)
	{
	case E_MOUSE_COLOR::DARK_GREY:
		m_Color = c_darkGrey;
		break;
	case E_MOUSE_COLOR::GREY:
		m_Color = c_grey;
		break;
	case E_MOUSE_COLOR::WHITE:
		m_Color = c_white;
		break;
	}
	runState = new MouseRunState(*this);
	dieState = new MouseDieState(*this);
	idleState = new MouseIdleState(*this);
	jumpState = new MouseJumpState(*this);
	walkState = new MouseWalkState(*this);
	hurtState = new MouseHurtState(*this);
	whackedState = new MouseWhackedState(*this);
	m_state = idleState;

}

Mouse::~Mouse()
{
}



void Mouse::SetMouseState(E_MOUSE_STATE e_state)
{
	e_mouseState = e_state;
	OnStateChange();
}

void Mouse::OnStateChange()
{
	switch (e_mouseState)
	{
	case E_MOUSE_STATE::runState:
		m_state = runState;
		break;
	case E_MOUSE_STATE::dieState:
		m_state = dieState;
		break;
	case E_MOUSE_STATE::idleState:
		m_state = idleState;
		break;
	case E_MOUSE_STATE::jumpState:
		m_state = jumpState;
		break;
	case E_MOUSE_STATE::walkState:
		m_state = walkState;
		break;
	case E_MOUSE_STATE::hurtState:
		m_state = hurtState;
		break;
	case E_MOUSE_STATE::whackedState:
		m_state = whackedState;
		break;
	default:
		m_state = idleState;
		break;
	}
}

void Mouse::DrawBoundingBox()
{
	Play::Point2D tl{ m_pos.x - Play::GetSpriteWidth(spriteName) / 2 * m_scale,m_pos.y - Play::GetSpriteHeight(spriteName) / 2 * m_scale };
	Play::Point2D br{ m_pos.x + Play::GetSpriteWidth(spriteName) / 2 * m_scale,m_pos.y + Play::GetSpriteHeight(spriteName) / 2 * m_scale };
	Play::DrawRect(tl, br, Play::cRed);
}

void Mouse::Update()
{
	if (!m_state)
		return;
	m_state->Update();
	DrawBoundingBox();
}

