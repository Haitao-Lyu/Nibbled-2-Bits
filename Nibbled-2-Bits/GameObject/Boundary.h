#pragma once
#include "Obstacle.h"
#include "Component/Collider.h"

enum class E_DIR_BOUNDARY
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};

class Boundary:public Obstacle
{
private:
	const char* tileName = "BounderTile";
	const char* cornerTileName = "BounderCorner";

	BoxCollider m_boxCollider;
	float m_scale = 1.25f;
	E_DIR_BOUNDARY m_dir = E_DIR_BOUNDARY::UP;
	bool isCorner = false;
	bool isMouseHole = false;
public:

	Boundary(Play::Point2D pos);
	~Boundary();
	void Update() override;
	void Render() override;
	void SetDirection(E_DIR_BOUNDARY dir);
	void SetCorner();
	BoxCollider& GetCollider();
};

