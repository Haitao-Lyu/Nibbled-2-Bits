#include "pch.h"
#include "MouseTrap.h"
#include "../MainGame.h"
static const char* trap_dark_wood = "Trap_dark_wood";
static const char* trap_dark_wood_not = "Trap_dark_wood_not";
static const char* trap_light_wood =	"Trap_light_wood";
static const char* trap_light_wood_not = "Trap_light_wood_not";

MouseTrap::MouseTrap(Play::Point2D pos, E_TRAPCOLOR color):ConsumableObj(pos,E_OBJTYPE::E_MOUSETRAP),m_color(color)
{
	OnColorChange();
	m_spriteWidth = Play::GetSpriteWidth(spriteName);
	m_spriteHeight = Play::GetSpriteHeight(spriteName);
	GetCollider().Init( m_spriteWidth * m_scale, m_spriteHeight * m_scale, m_pos, this);
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
	Render();
	
}

void MouseTrap::Render()
{
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	if (m_rot == 90 || m_rot == 270)
	{
		GetCollider().UpdateShape(m_spriteHeight, m_spriteWidth, m_pos);
	}
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale ,0.0f,0.0f },
		{ 0.0f,m_scale ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);
	m_boxCollider.DrawBoundingBox();
}
