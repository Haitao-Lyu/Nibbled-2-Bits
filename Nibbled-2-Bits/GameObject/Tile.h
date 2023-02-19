#pragma once
#include "Obstacle.h"
enum class E_TILE_COLOR
{
	BLUE,
	GREEN,
	PINK,
	YELLOW
};

class Tile:public Obstacle
{
private:
	const char* single = "BlueTile_single";
	const char* top = "BlueTile_vertical_top";
	const char* btm = "BlueTile_vertical_bottom";
	const char* left = "BlueTile_horizontal_left";
	const char* right = "BlueTile_horizontal_right";
	E_TILE_COLOR m_color;
public:
	Tile(Play::Point2D pos, E_TILE_COLOR color = E_TILE_COLOR::BLUE);
	~Tile();

};

