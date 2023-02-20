#include "pch.h"
#include "Tile.h"
#include "../MainGame.h"
Tile::Tile(Play::Point2D pos, E_TILE_COLOR color) :Obstacle(pos,E_OBJTYPE::E_TILE)
{
	spriteName = "BlueTile_single";
	m_color = color;
}

Tile::~Tile()
{
}

void Tile::Update()
{
	Render();
	//DrawBoundingBox();
}



void Tile::Render()
{
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scale ,0.0f,0.0f },
		{ 0.0f,m_scale ,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y,0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt, 0);
}

void Tile::DrawBoundingBox()
{
	Play::Point2D tl{ m_pos.x - Play::GetSpriteWidth(spriteName) / 2 * m_scale,m_pos.y - Play::GetSpriteHeight(spriteName) / 2 * m_scale };
	Play::Point2D br{ m_pos.x + Play::GetSpriteWidth(spriteName) / 2 * m_scale,m_pos.y + Play::GetSpriteHeight(spriteName) / 2 * m_scale };
	Play::DrawRect(tl, br, Play::cRed);
}

