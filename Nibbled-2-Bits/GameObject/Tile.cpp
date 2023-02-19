#include "Tile.h"
Tile::Tile(Play::Point2D pos, E_TILE_COLOR color) :Obstacle(pos,E_OBJTYPE::E_TILE)
{
	spriteName = "BlueTile_single";
	m_color = color;
}

Tile::~Tile()
{
}