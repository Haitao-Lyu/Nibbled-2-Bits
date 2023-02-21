#include "pch.h"
#include "Mouse.h"
#include "../GameTool/DebugTool.h"
#include "Component/CollisionSystem.h"
#include "GameObjectMgr.h"
#include "Tile.h"
#include "Boundary.h"

Mouse::Mouse(Play::Point2D pos, E_MOUSE_COLOR COLOR): GameObject(pos,E_OBJTYPE::E_MOUSE)
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
void Mouse::MouseControl()
{
	if (Play::KeyDown(VK_UP))
	{
		m_pos.y -= m_speed;
		m_dir = E_MOUSE_DIR::UP;
		m_boxCollider.UpdateShape(m_width, m_height, m_pos);
		SetMouseState(E_MOUSE_STATE::walkState);
	}
	else if (Play::KeyDown(VK_DOWN))
	{
		m_pos.y += m_speed;
		m_dir = E_MOUSE_DIR::DOWN;
		m_boxCollider.UpdateShape(m_width, m_height, m_pos);
		SetMouseState(E_MOUSE_STATE::walkState);
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		m_pos.x += m_speed;
		m_dir = E_MOUSE_DIR::RIGHT;
		m_boxCollider.UpdateShape(m_height, m_width, m_pos);
		SetMouseState(E_MOUSE_STATE::walkState);
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		m_pos.x -= m_speed;
		m_dir = E_MOUSE_DIR::LEFT;
		m_boxCollider.UpdateShape(m_height, m_width, m_pos);
		SetMouseState(E_MOUSE_STATE::walkState);
	}
}

void Mouse::SetPosition(Play::Point2D pos)
{
	m_pos = pos;
}

BoxCollider& Mouse::GetCollider()
{
	return m_boxCollider;
}

Play::Point2D Mouse::GetPrevPos()
{
	return prev_pos;
}


void Mouse::Update()
{
	//record last frame pos
	prev_pos = m_pos;

	if (!m_state)
		return;
	SetMouseState(E_MOUSE_STATE::idleState);
	MouseControl();
	m_state->Update();
	//debug collision box
	m_boxCollider.DrawBoundingBox();

	//Get Tile obj list and calculate collision // And block mouse moving
	std::vector<GameObject*> &list = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_TILE);
	for (GameObject* obj : list)
	{
		Tile* tile = static_cast<Tile*>(obj);
		if (m_boxCollider.collidesWith(tile->GetCollider()))
		{
			m_pos = prev_pos;
			DebugValue(tile->GetID(),"collides:", 50);
			//GameObjectMgr::RemoveGameObjectByid(obj->m_id);
		}
	}

	//Get Tile obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_boundary = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_BOUNDARY);
	for (GameObject* obj : list_boundary)
	{
		Boundary* tile = static_cast<Boundary*>(obj);
		if (m_boxCollider.collidesWith(tile->GetCollider()))
		{
			m_pos = prev_pos;
			DebugValue(tile->GetID(), "collides:", 50);
			//GameObjectMgr::RemoveGameObjectByid(obj->m_id);
		}
	}
}
