#pragma once
#include "Obstacle.h"

enum class E_TUBE_COLOR
{

};

enum class E_TUBE_TYPE
{
	CROSS,
	ONEWAY,
	TWOWAY,
	THREEWAY,
};

class Tube:public Obstacle
{
private:
	E_TUBE_TYPE tube_type = E_TUBE_TYPE::CROSS;
	Play::Point2D origin_Pos{0.0f,0.0f};
	
public:
	
	Tube(Play::Point2D pos, E_TUBE_TYPE type = E_TUBE_TYPE::CROSS);

	void OnTypeChange();

	void Update() override;

	void Render() override;

};