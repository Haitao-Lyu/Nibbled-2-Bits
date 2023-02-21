#pragma once
#include "Obstacle.h"
#include "Component/Collider.h"
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
	BoxCollider m_boxCollider;
	float m_scale{ 1.0f };
	float m_colliderScale{ 0.8f};
	E_TILE_COLOR m_color;
public:
	Tile(Play::Point2D pos, E_TILE_COLOR color = E_TILE_COLOR::BLUE);
	~Tile();
	void Update() override;
	void Render() override;
	void SetTileType();
	BoxCollider& GetCollider();
};

