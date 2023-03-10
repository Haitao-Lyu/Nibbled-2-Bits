#pragma once
#include "Obstacle.h"

enum class E_TILE_COLOR
{
	BLUE,
	GREEN,
	PINK,
	YELLOW
};

enum class E_TILE_TYPE
{
	//2 BEND
	BBR,
	BTL,
	BTR,
};


class Tile:public Obstacle
{
private:
	E_TILE_COLOR m_color;
public:
	Tile(Play::Point2D pos, E_TILE_COLOR color = E_TILE_COLOR::GREEN);
	~Tile();
	void Update() override;
	void Render() override;
	void SetTileType();

};

