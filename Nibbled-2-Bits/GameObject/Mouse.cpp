#include "pch.h"
#include "Mouse.h"
#include "../GameTool/DebugTool.h"
#include "Component/CollisionSystem.h"
#include "../Manager/GameObjectMgr.h"
#include "../Manager/LevelMgr.h"
#include "Tile.h"
#include "Boundary.h"
#include "MouseTrap.h"
#include "Cheese.h"
#include "MouseHole.h"
#include "Tube.h"
#include "../UI/EventCenter.h"
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
	m_state = &m_idleState;
	//when game start btn pressed recevice the event // TODO: need to fix memory leak

	EventListener startListener("MouseStartGameListener");// how to distinguish different listener

	startListener.addEvent([this]() 
		{
			this->SetMouseState(E_MOUSE_STATE::walkState);
		});

	EventCenter::RegisterListener("GameStart", startListener); 
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

	m_state = &m_idleState;

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
		m_state = &m_runState;
		break;
	case E_MOUSE_STATE::dieState:
		m_state = &m_dieState;
		break;
	case E_MOUSE_STATE::idleState:
		m_state = &m_idleState;
		break;
	case E_MOUSE_STATE::jumpState:
		m_state = &m_jumpState;
		break;
	case E_MOUSE_STATE::walkState:
		m_state = &m_walkState;
		break;
	case E_MOUSE_STATE::hurtState:
		m_state = &m_hurtState;
		break;
	case E_MOUSE_STATE::whackedState:
		m_state = &m_whackedState;
		break;
	default:
		m_state = &m_idleState;
		break;
	}
}
void Mouse::DebugMouseControl()
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
			Rotate(90);
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
			Rotate(90);
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
			Rotate(90);
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

	//Get mousehole obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_hole = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_MOUSEHOLE);
	for (GameObject* obj : list_hole)
	{
		if (!obj)//check pointer valid
			break;
		MouseHole* hole = static_cast<MouseHole*>(obj);
		if (m_circleCollider.collidesWith(hole->GetCollider()))
		{
			if (hole->m_type == E_MOUSEHOLE_TYPE::ENTRY)
			{
				Rotate(180);
			}
			hole->OnMouseIn(*this);
			DebugValue(hole->GetID(), "collides:", 50);
		}

	}

	//Get mousehole obj list and calculate collision // And block mouse moving
	std::vector<GameObject*>& list_tube = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_TUBE);
	for (GameObject* obj : list_tube)
	{
		if (!obj)//check pointer valid
			break;
		Tube* tube = static_cast<Tube*>(obj);
		if (m_circleCollider.collidesWith(tube->GetCollider()))
		{
			tube->CollideMouse(this);
			DebugValue(tube->GetID(), "collides:", 50);
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
	//DebugMouseControl();

	//CheckBoxCollision();
	CheckCircleCollision();

	if (isWhacked)
		SetMouseState(E_MOUSE_STATE::whackedState);

	if (isDead)
		SetMouseState(E_MOUSE_STATE::dieState);
	//draw eveything at the end
	m_state->Update(this);
}

void Mouse::Rotate(float rot)
{

	m_rot += rot;
	while (m_rot < 0)
	{
		m_rot += 360;
	}
	while (m_rot >= 360)
	{
		m_rot -= 360;
	}
	OnRotationChanged();
}

void Mouse::SetRotation(float rot)
{
	m_rot = rot;
	while (m_rot < 0)
	{
		m_rot += 360;
	}
	while (m_rot >= 360)
	{
		m_rot -= 360;
	}
	OnRotationChanged();
}

void Mouse::OnRotationChanged()
{
	//when rotation change, set it to snap to grid position
	EventCenter::PostEvent("MouseRotationChanged");

	//Snap to Grid
	Level* lev = LevelMgr::GetInstance()->GetCurrentLevel();
	float minDis = 10000;
	GridItem* closestGrid = nullptr;
	//could do math to accelerate
	for (std::vector<GridItem>& grids : lev->GetGamePanel()->gridComponent.gridList)
	{
		for (GridItem& grid : grids)
		{
			float dis = (m_pos - grid.GetPos()).Length();
			if (dis < minDis)
			{
				minDis = dis;
				closestGrid = &grid;
			}
		}
	}
	if (closestGrid)
	{
		closestGrid->DrawGrid(Play::cBlue);

		if (m_rot == 0.0f)
		{
			m_dir = E_MOUSE_DIR::UP;
			m_pos.x = closestGrid->GetPos().x;
		}
		if (m_rot == 90.0f)
		{
			m_dir = E_MOUSE_DIR::LEFT;
			m_pos.y = closestGrid->GetPos().y;
		}
		else if (m_rot == 180.0f)
		{
			m_dir = E_MOUSE_DIR::DOWN;
			m_pos.x = closestGrid->GetPos().x;
		}
		else if (m_rot == 270.0f)
		{
			m_dir = E_MOUSE_DIR::RIGHT;
			m_pos.y = closestGrid->GetPos().y;
		}
		closestGrid = nullptr;
	}
}
