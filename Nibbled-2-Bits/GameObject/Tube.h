#pragma once
#include "Obstacle.h"
#include "Mouse.h"
enum class E_TUBE_COLOR
{

};

enum class E_TUBE_TYPE
{
	ONEWAY,
	TWOWAY,
	THREEWAY,
	CROSS,
};

class Tube:public Obstacle
{
private:
	E_TUBE_TYPE tube_type = E_TUBE_TYPE::CROSS;
	Play::Vector2D normal_line{ 0.0f,0.0f };
	Play::Vector2D right_line{ 0.0f,0.0f };
	Play::Vector2D left_line{ 0.0f,0.0f };
	Play::Vector2D inverseNormal_line{ 0.0f,0.0f };
	int mouse_cur_dir = -1;
public:
	
	Tube(Play::Point2D pos, E_TUBE_TYPE type = E_TUBE_TYPE::CROSS);

	void Rotate(float rot) override;

	void SetType(E_TUBE_TYPE type);

	void OnTypeChange();

	void OnDirctionChange(float rot);

	void Update() override;

	void Render() override;

	void DrawTubeOpenDir();

	void CollideMouse(Mouse *mice);

};