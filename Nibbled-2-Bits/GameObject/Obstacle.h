#pragma once
#include "GameObject.h"
#include "../PlayCustom.h"

enum class E_TILE_COLOR
{
	BLUE,
	GREEN,
	PINK,
	YELLOW
};
class Obstacle:public GameObject
{
private:
	E_TILE_COLOR m_color = E_TILE_COLOR::BLUE;
public:
	Obstacle(Play::Point2D pos, E_TILE_COLOR color = E_TILE_COLOR::BLUE);
	~Obstacle();

	void Update() override;
};

