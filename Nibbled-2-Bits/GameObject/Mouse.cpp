#include "pch.h"
#include "Mouse.h"
#include "../GameTool/DebugTool.h"
#include "Component/CollisionSystem.h"
#include "../Manager/GameObjectMgr.h"
#include "Tile.h"
#include "Boundary.h"
#include "MouseTrap.h"
#include "Cheese.h"
#include "MouseHole.h"
//particle effect follow the mouse
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

BoxCollider& Mouse::GetBoxCollider()
{
	return m_boxCollider;
}

CircleCollider& Mouse::GetCollider()
{
	return m_circleCollider;
}

Play::Point2D Mouse::GetPrevPos()
{
	return prev_pos;
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
		m_boxCollider.UpdateShape(m_spriteWidth, m_spriteHeight, m_pos);
		SetMouseState(E_MOUSE_STATE::walkState);
	}
	else if (Play::KeyDown(VK_DOWN))
	{
		m_pos.y += m_speed;
		m_dir = E_MOUSE_DIR::DOWN;
		m_boxCollider.UpdateShape(m_spriteWidth, m_spriteHeight, m_pos);
		SetMouseState(E_MOUSE_STATE::walkState);
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		m_pos.x += m_speed;
		m_dir = E_MOUSE_DIR::RIGHT;
		m_boxCollider.UpdateShape(m_spriteHeight, m_spriteWidth, m_pos);
		SetMouseState(E_MOUSE_STATE::walkState);
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		m_pos.x -= m_speed;
		m_dir = E_MOUSE_DIR::LEFT;
		m_boxCollider.UpdateShape(m_spriteHeight, m_spriteWidth, m_pos);
		SetMouseState(E_MOUSE_STATE::walkState);
	}
	else
	SetMouseState(E_MOUSE_STATE::idleState);
}

void Mouse::SetPosition(Play::Point2D pos)
{
	m_pos = pos;
}

void Mouse::CheckBoxCollision()
{
	//debug collision box
	m_boxCollider.DrawBoundingBox();
	//Get Tile obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_MOUSE = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_MOUSE);
	for (GameObject* obj : list_MOUSE)
	{
		Mouse* mouse = static_cast<Mouse*>(obj);
		if (m_boxCollider.collidesWith(mouse->GetBoxCollider()))
		{
			m_pos = prev_pos;
			DebugValue(mouse->GetID(), "collides:", 50);
			//GameObjectMgr::RemoveGameObjectByid(obj->m_id);
		}
	}
	//Get Tile obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_tile = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_TILE);
	for (GameObject* obj : list_tile)
	{
		Tile* tile = static_cast<Tile*>(obj);
		if (m_boxCollider.collidesWith(tile->GetBoxCollider()))
		{
			Play::Vector2D dir = normalize(prev_pos - m_pos);
			m_pos = prev_pos;
			//if (m_boxCollider.collidesWith(tile->GetCollider()))
			//{
			//	m_pos += dir * 10;
			//}
			DebugValue(tile->GetID(), "collides:", 50);
			//GameObjectMgr::RemoveGameObjectByid(obj->m_id);
		}
	}
	//Get Tile obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_boundary = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_BOUNDARY);
	for (GameObject* obj : list_boundary)
	{
		Boundary* tile = static_cast<Boundary*>(obj);
		if (m_boxCollider.collidesWith(tile->GetBoxCollider()))
		{
			m_pos = prev_pos;
			DebugValue(tile->GetID(), "collides:", 50);
			//GameObjectMgr::RemoveGameObjectByid(obj->m_id);
		}
	}
	//Get Tile obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_Trap = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_MOUSETRAP);
	for (GameObject* obj : list_Trap)
	{
		MouseTrap* trap = static_cast<MouseTrap*>(obj);
		if (m_boxCollider.collidesWith(trap->GetBoxCollider()))
		{
			isWhacked = true;
			trap->SetActive(true);
			DebugValue(trap->GetID(), "collides:", 50);
		}
	}
	//Get cheese obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_CZ = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_CHEESE);
	for (GameObject* obj : list_CZ)
	{
		Cheese* cz = static_cast<Cheese*>(obj);
		if (m_boxCollider.collidesWith(cz->GetBoxCollider()))
		{
			cz->SetIsConsumed(true);
			DebugValue(cz->GetID(), "collides:", 50);
		}
	}

}

void Mouse::CheckCircleCollision()
{
	m_circleCollider.Init(m_pos, m_spriteWidth / 2 * m_scale);
	//m_circleCollider.DrawBoundingBox();
	//Mouse
	std::vector<GameObject*>& list_MOUSE = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_MOUSE);
	for (GameObject* obj : list_MOUSE)
	{
		if (!obj)//check pointer valid
			break;
		if (obj->GetID() == m_id)
			continue;//except it self
		Mouse* mouse = static_cast<Mouse*>(obj);
		CircleCollider& collider = mouse->GetCollider();
		if (m_circleCollider.collidesWith(collider))
		{
			//move obj backward based on the distance and direction between two obj
			Play::Vector2D dir = normalize(m_pos - mouse->m_pos);
			m_pos = mouse->m_pos + collider.GetRadius() * dir + m_circleCollider.GetRadius() * dir;
			DebugValue(mouse->GetID(), "collides:", 50);
		}
	}
	//Get Tile obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_boundary = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_BOUNDARY);

	for (GameObject* obj : list_boundary)
	{
		if (!obj)//check pointer valid
			break;
		Boundary* boundary = static_cast<Boundary*>(obj);
		CircleCollider& collider = boundary->GetCollider();
		if (m_circleCollider.collidesWith(collider))
		{
			//move obj backward based on the distance and direction between two obj
			Play::Vector2D dir = normalize(m_pos - boundary->m_pos);
			m_pos = boundary->m_pos + collider.GetRadius() * dir + m_circleCollider.GetRadius() * dir;
			DebugValue(boundary->GetID(), "collides:", 50);
		}
	}

	//Get Tile obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_tile = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_TILE);
	for (GameObject* obj : list_tile)
	{
		if (!obj)//check pointer valid
			break;
		Tile* tile = static_cast<Tile*>(obj);
		CircleCollider& collider = tile->GetCollider();
		if (m_circleCollider.collidesWith(collider))
		{
			//move obj backward based on the distance and direction between two obj
			Play::Vector2D dir = normalize(m_pos - tile->m_pos );
			m_pos = tile->m_pos + collider.GetRadius() * dir + m_circleCollider.GetRadius() * dir;
			DebugValue(tile->GetID(), "collides:", 50);
		}
	}

	//Get Tile obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_Trap = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_MOUSETRAP);
	for (GameObject* obj : list_Trap)
	{
		if (!obj)//check pointer valid
			break;
		MouseTrap* trap = static_cast<MouseTrap*>(obj);
		if (m_circleCollider.collidesWith(trap->GetCollider()))
		{
			isWhacked = true;
			trap->SetActive(true);
			DebugValue(trap->GetID(), "collides:", 50);
		}
	}

	//Get cheese obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_CZ = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_CHEESE);
	for (GameObject* obj : list_CZ)
	{
		if (!obj)//check pointer valid
			break;
		Cheese* cz = static_cast<Cheese*>(obj);
		if (m_circleCollider.collidesWith(cz->GetCollider()))
		{
			cz->SetIsConsumed(true);
			DebugValue(cz->GetID(), "collides:", 50);
		}
	}

	//Get cheese obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_hole = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::	E_MOUSEHOLE);
	for (GameObject* obj : list_hole)
	{
		if (!obj)//check pointer valid
			break;
		MouseHole* hole = static_cast<MouseHole*>(obj);
		if (m_circleCollider.collidesWith(hole->GetCollider()))
		{
			hole->OnMouseIn(*this);
			DebugValue(hole->GetID(), "collides:", 50);
		}
	}
}


void Mouse::Update()
{
	//record last frame pos
	prev_pos = m_pos;

	if (!m_state)
		return;
	//movement
	MouseControl();

	//CheckBoxCollision();
	CheckCircleCollision();

	if (isWhacked)
		SetMouseState(E_MOUSE_STATE::whackedState);

	if (isDead)
		SetMouseState(E_MOUSE_STATE::dieState);

	//draw eveything at the end
	m_state->Update();
}

void Mouse::SetInitRotation(float dir)
{
	m_rot = dir;
	if (m_rot == 90.0f)
	{
		m_dir = E_MOUSE_DIR::LEFT;
	}
	else if (m_rot == 180.0f)
	{
		m_dir = E_MOUSE_DIR::DOWN;
	}
	else if (m_rot == 270.0f)
	{
		m_dir = E_MOUSE_DIR::RIGHT;
	}
}
