#include "pch.h"
#include "Boundary.h"
#include "../MainGame.h"

static const Play::Matrix2D dir_left = Play::MatrixRotation(Play::DegToRad(90.0f));
static const Play::Matrix2D dir_down = Play::MatrixRotation(Play::DegToRad(180.0f));
static const Play::Matrix2D dir_right = Play::MatrixRotation(Play::DegToRad(270.0f));
static const Play::Matrix2D dir_up = Play::MatrixIdentity();

Boundary::Boundary(Play::Point2D pos):Obstacle(pos,E_OBJTYPE::E_BOUNDARY)
{
	SetScale(1.15f);
	m_boxCollider.Init(Play::GetSpriteWidth(tileName) * m_scale, Play::GetSpriteHeight(tileName) * m_scale, pos, this);
	m_circleCollider.Init(pos , (Play::GetSpriteWidth(tileName)/2 )  * m_scale);
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

	//change direction based on position
	Play::Matrix2D rtMt;
	switch (m_dir)
	{
	case E_DIR_BOUNDARY::UP:
		rtMt = dir_up;
		break;
	case E_DIR_BOUNDARY::LEFT:
		rtMt = dir_left;
		m_boxCollider.UpdateShape(Play::GetSpriteHeight(tileName) * m_scale, Play::GetSpriteWidth(tileName) * m_scale, m_pos);
		break;
	case E_DIR_BOUNDARY::DOWN:
		rtMt = dir_down;
		break;
	case E_DIR_BOUNDARY::RIGHT:
		rtMt = dir_right;
		m_boxCollider.UpdateShape(Play::GetSpriteHeight(tileName) * m_scale, Play::GetSpriteWidth(tileName) * m_scale, m_pos);
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
	//m_circleCollider.DrawBoundingBox(Play::cBlue);
	//m_boxCollider.DrawBoundingBox();
	//TODO: REFACTOR SQAURE COLLDIER
}

void Boundary::SetDirection(E_DIR_BOUNDARY dir)
{
	m_dir = dir;
}

void Boundary::SetCorner()
{
	isCorner = true;
}

