#include "pch.h"
#include "MouseTrap.h"
#include "../MainGame.h"
#include "../GameTool/Timer.h"
#include "GameObjectMgr.h"

static const char* trap_dark_wood = "Trap_dark_wood";
static const char* trap_dark_wood_not = "Trap_dark_wood_not";
static const char* trap_light_wood =	"Trap_light_wood";
static const char* trap_light_wood_not = "Trap_light_wood_not";

MouseTrap::MouseTrap(Play::Point2D pos, E_TRAPCOLOR color):ConsumableObj(pos,E_OBJTYPE::E_MOUSETRAP),m_color(color)
{
	OnColorChange();
	m_spriteWidth = Play::GetSpriteWidth(spriteName);
	m_spriteHeight = Play::GetSpriteHeight(spriteName);
	GetBoxCollider().Init( m_spriteWidth * m_scale, m_spriteHeight * m_scale, m_pos, this);
	GetCollider().Init(pos, m_spriteWidth * m_scale / 2);
	//const char* text can't be changed ?
}

MouseTrap::~MouseTrap()
{
}

void MouseTrap::SetColor(E_TRAPCOLOR color)
{
	m_color = color;
	OnColorChange();
}

void MouseTrap::SetActive(bool active)
{
	isActived = active;
}

void MouseTrap::OnColorChange()
{
	switch (m_color)
	{
	case E_TRAPCOLOR::DARK_WOOD:
		spriteName = trap_dark_wood;
		break;
	case E_TRAPCOLOR::LIGHT_WOOD:
		spriteName = trap_light_wood;
		break;
	default:
		break;
	}
}

void MouseTrap::Update()
{
	if (isActived)
	{
		switch (m_color)
		{
		case E_TRAPCOLOR::DARK_WOOD:
			spriteName = trap_dark_wood_not;
			break;
		case E_TRAPCOLOR::LIGHT_WOOD:
			spriteName = trap_light_wood_not;
			break;
		default:
			break;
		}
		//set timer to delay destroy itself
		static Timer timer(1.0f);
		if (timer.isReachTimeInterval())
		{
			GameObjectMgr::RemoveGameObject(*this);
		}
	}
	Render();
	//m_boxCollider.DrawBoundingBox();
	//m_circleCollider.DrawBoundingBox(Play::cRed);
}

void MouseTrap::Render()
{
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	//render collider position
	if (m_rot == 90 || m_rot == 270)
	{
		GetBoxCollider().UpdateShape(m_spriteHeight, m_spriteWidth, m_pos);
	}
	//movement matrix
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale ,0.0f,0.0f },
		{ 0.0f,m_scale ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);

}
