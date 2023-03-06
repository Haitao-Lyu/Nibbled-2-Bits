#pragma once
#include "Obstacle.h"
#include "Component/BoxCollider.h"
#include "Component/CircleCollider.h"

enum class E_DIR_BOUNDARY
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};

enum class E_BOUNDARY_COLOR
{
	WHITE,
	WOOD
};

class Boundary:public Obstacle
{
private:
	const char* cornerTileName = "BounderCorner";
	E_BOUNDARY_COLOR m_color_type = E_BOUNDARY_COLOR::WHITE;
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

};

