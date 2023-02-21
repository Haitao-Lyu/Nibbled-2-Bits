#include "pch.h"
#include "Tile.h"
#include "../MainGame.h"
#include "GameObjectMgr.h"
#include "../GameTool/DebugTool.h"
#include "Mouse.h"
Tile::Tile(Play::Point2D pos, E_TILE_COLOR color) :Obstacle(pos,E_OBJTYPE::E_TILE)
{
	spriteName = "BlueTile_single";
	m_color = color;
	m_boxCollider.Init(Play::GetSpriteWidth("BlueTile_single") * m_colliderScale, Play::GetSpriteHeight("BlueTile_single") * m_colliderScale, m_pos, this);
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

BoxCollider& Tile::GetCollider()
{
	return m_boxCollider;
}


