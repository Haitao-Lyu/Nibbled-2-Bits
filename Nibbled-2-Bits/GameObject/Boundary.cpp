#include "pch.h"
#include "Boundary.h"
#include "../MainGame.h"

static const Play::Matrix2D dir_left = Play::MatrixRotation(Play::DegToRad(90.0f));
static const Play::Matrix2D dir_down = Play::MatrixRotation(Play::DegToRad(180.0f));
static const Play::Matrix2D dir_right = Play::MatrixRotation(Play::DegToRad(270.0f));
static const Play::Matrix2D dir_up = Play::MatrixIdentity();

static const char* bottom_name = "boundary_bottom";
static const char* left_name = "boundary_left";
static const char* right_name = "boundary_right";
static const char* top_name = "boundary_top";
static const char* boundary_inner_corner_bottom_left_name = "boundary_inner_corner_bottom_left";
static const char* boundary_inner_corner_bottom_right_name = "boundary_inner_corner_bottom_right";
static const char* boundary_inner_corner_top_left_name = "boundary_inner_corner_top_left";
static const char* boundary_inner_corner_top_right_name = "boundary_inner_corner_top_right";

static const char* white_bottom_name = "white_bottom";
static const char* white_left_name =  "white_left";
static const char* white_right_name = "white_right";
static const char* white_top_name =   "white_top";
static const char* white_boundary_inner_corner_bottom_left_name =   "white_inner_corner_bottom_left";
static const char* white_boundary_inner_corner_bottom_right_name =  "white_inner_corner_bottom_right";
static const char* white_boundary_inner_corner_top_left_name =		"white_inner_corner_top_left";
static const char* white_boundary_inner_corner_top_right_name =		"white_inner_corner_top_right";
Boundary::Boundary(Play::Point2D pos):Obstacle(pos,E_OBJTYPE::E_BOUNDARY)
{
	spriteName = "boundary_top";
	m_boxCollider.Init(Play::GetSpriteWidth(spriteName) * m_scale, Play::GetSpriteHeight(spriteName) * m_scale, pos, this);
	m_circleCollider.Init(pos , (Play::GetSpriteWidth(spriteName)/3)  * m_scale);
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

	switch (m_color_type)
	{
	case E_BOUNDARY_COLOR::WHITE:
	{
		switch (m_dir)
		{
		case E_DIR_BOUNDARY::UP:
			cornerTileName = white_boundary_inner_corner_top_left_name;
			spriteName = white_top_name;
			break;
		case E_DIR_BOUNDARY::LEFT:
			cornerTileName = white_boundary_inner_corner_bottom_left_name;
			spriteName = white_left_name;
			m_boxCollider.UpdateShape(Play::GetSpriteHeight(spriteName) * m_scale, Play::GetSpriteWidth(spriteName) * m_scale, m_pos);
			break;
		case E_DIR_BOUNDARY::DOWN:
			cornerTileName = white_boundary_inner_corner_bottom_right_name;
			spriteName = white_bottom_name;
			break;
		case E_DIR_BOUNDARY::RIGHT:
			cornerTileName = white_boundary_inner_corner_top_right_name;
			spriteName = white_right_name;
			m_boxCollider.UpdateShape(Play::GetSpriteHeight(spriteName) * m_scale, Play::GetSpriteWidth(spriteName) * m_scale, m_pos);
			break;
		default:
			break;
		}
	}
		break;
	case E_BOUNDARY_COLOR::WOOD:
	{
		switch (m_dir)
		{
		case E_DIR_BOUNDARY::UP:
			cornerTileName = boundary_inner_corner_top_left_name;
			spriteName = top_name;
			break;
		case E_DIR_BOUNDARY::LEFT:
			cornerTileName = boundary_inner_corner_bottom_left_name;
			spriteName = left_name;
			m_boxCollider.UpdateShape(Play::GetSpriteHeight(spriteName) * m_scale, Play::GetSpriteWidth(spriteName) * m_scale, m_pos);
			break;
		case E_DIR_BOUNDARY::DOWN:
			cornerTileName = boundary_inner_corner_bottom_right_name;
			spriteName = bottom_name;
			break;
		case E_DIR_BOUNDARY::RIGHT:
			cornerTileName = boundary_inner_corner_top_right_name;
			spriteName = right_name;
			m_boxCollider.UpdateShape(Play::GetSpriteHeight(spriteName) * m_scale, Play::GetSpriteWidth(spriteName) * m_scale, m_pos);
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}
	//change direction based on position
	
	if (isCorner)
	{
		Play::DrawSpriteTransformed(Play::GetSpriteId(cornerTileName), scaleMt, 0);
	}
	else
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt , 0);
	m_circleCollider.DrawBoundingBox(Play::cBlue);
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

