#include "pch.h"
#include "Boundary.h"
#include "../MainGame.h"

static const Play::Matrix2D dir_left = Play::MatrixRotation(Play::DegToRad(90.0f));
static const Play::Matrix2D dir_down = Play::MatrixRotation(Play::DegToRad(180.0f));
static const Play::Matrix2D dir_right = Play::MatrixRotation(Play::DegToRad(270.0f));
static const Play::Matrix2D dir_up = Play::MatrixIdentity();

Boundary::Boundary(Play::Point2D pos):Obstacle(pos,E_OBJTYPE::E_BOUNDARY)
{
	m_boxCollider.Init(Play::GetSpriteWidth(tileName), Play::GetSpriteHeight(tileName), pos, this);
}

Boundary::~Boundary()
{
}

void Boundary::Update()
{
	Render();
}

void Boundary::Render()
{
	
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale ,0.0f,0.0f },
		{ 0.0f,m_scale ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });

	Play::Matrix2D rtMt;
	switch (m_dir)
	{
	case E_DIR_BOUNDARY::UP:
		rtMt = dir_up;
		break;
	case E_DIR_BOUNDARY::LEFT:
		rtMt = dir_left;
		m_boxCollider.UpdateShape(Play::GetSpriteHeight(tileName), Play::GetSpriteWidth(tileName), m_pos);
		break;
	case E_DIR_BOUNDARY::DOWN:
		rtMt = dir_down;
		break;
	case E_DIR_BOUNDARY::RIGHT:
		rtMt = dir_right;
		m_boxCollider.UpdateShape(Play::GetSpriteHeight(tileName), Play::GetSpriteWidth(tileName), m_pos);
		break;
	default:
		break;
	}
	if (isCorner)
	{
		Play::DrawSpriteTransformed(Play::GetSpriteId(cornerTileName), scaleMt * rtMt, 0);
	}
	else
	Play::DrawSpriteTransformed(Play::GetSpriteId(tileName), scaleMt * rtMt, 0);
	m_boxCollider.DrawBoundingBox();
	//m_boxCollider.DrawBoundingBox();
}

void Boundary::SetDirection(E_DIR_BOUNDARY dir)
{
	m_dir = dir;
}

void Boundary::SetCorner()
{
	isCorner = true;
}

BoxCollider& Boundary::GetCollider()
{
	return m_boxCollider;
}
