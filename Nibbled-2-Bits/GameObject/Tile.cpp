#include "pch.h"
#include "Tile.h"
#include "../MainGame.h"
#include "GameObjectMgr.h"
#include "../GameTool/DebugTool.h"
#include "Mouse.h"

static const char* blue_single = "BlueTile_single";
static const char* blue_top = "BlueTile_vertical_top";
static const char* blue_btm = "BlueTile_vertical_bottom";
static const char* blue_left = "BlueTile_horizontal_left";
static const char* blue_right = "BlueTile_horizontal_right";

static const char* green_single =	"green_single";
static const char* green_top =		"green_vertical_top";
static const char* green_btm =		"green_vertical_bottom";
static const char* green_left =		"green_horizontal_left";
static const char* green_right =	"green_horizontal_right";

Tile::Tile(Play::Point2D pos, E_TILE_COLOR color) :Obstacle(pos,E_OBJTYPE::E_TILE)
{
	
	switch (color)
	{
	case E_TILE_COLOR::BLUE:
		spriteName = blue_single;
		break;
	case E_TILE_COLOR::GREEN:
		spriteName = green_single;
		break;
	case E_TILE_COLOR::PINK:
		break;
	case E_TILE_COLOR::YELLOW:
		break;
	default:
		break;
	}
	m_color = color;
	m_boxCollider.Init(Play::GetSpriteWidth(spriteName) * m_colliderScale, Play::GetSpriteHeight(spriteName) * m_colliderScale, m_pos, this);
}

Tile::~Tile()
{
	delete this;
}

void Tile::Update()
{
	//std::vector<GameObject*> &list = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_MOUSE);
	//for (GameObject* obj : list)
	//{
	//	Mouse* mice = static_cast<Mouse*>(obj);
	//	if (m_boxCollider.collidesWith(mice->GetCollider()))
	//	{
	//		mice->SetPosition(mice->GetPrevPos());
	//		DebugValue(m_id,"colldier:", 50);
	//	}
	//}
	Render();
}


void Tile::Render()
{
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale ,0.0f,0.0f },
		{ 0.0f,m_scale ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt, 0);
	m_boxCollider.DrawBoundingBox();
}

void Tile::SetTileType()
{
}

BoxCollider& Tile::GetCollider()
{
	return m_boxCollider;
}


